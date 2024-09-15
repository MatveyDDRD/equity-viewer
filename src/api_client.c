#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include "../cjson/cJSON.h"
#include "dynArray.h"

// апи ключ - RE6GIKKZ0EQJIOMG

// struct that have data of bar
typedef struct {
    float open;
    float high;
    float low;
    float close;
    float volume;
} bar;

typedef enum { 
    ONEMIN,
    FIVEMIN,
    FIVETEENMIN, 
    HALFOFHOUR, 
    HOUR
} interval;

typedef enum {
    REFRESH_LIST_INTRADAY,
    SEARCH_BAR
} apiCallAction;

char* getIntervalString(interval interval) {
    switch(interval) {
        case ONEMIN: return "1min";
        case FIVEMIN: return "5min";
        case FIVETEENMIN: return "15min";
        case HALFOFHOUR: return "30min";
        case HOUR: return "60min";
        default: return "";
    }
}

char* makeApiCallUrl(apiCallAction act, interval interval, char* symbol, char* apikey) {
    char url[128];

    strcpy(url, "https://www.alphavantage.co/query?function=");

    switch (act) {
        case REFRESH_LIST_INTRADAY:
            strcat(url, "TIME_SERIES_INTRADAY");
            strcat(url, "&symbol=");
            strcat(url, symbol);
            strcat(url, "&interval=");
            strcat(url, getIntervalString(interval));
            strcat(url, "&apikey=");
            strcat(url, apikey);
            break;
        case SEARCH_BAR:
            break;
    }

    char *ret = malloc(strlen(url) + 1);
    if (ret != NULL) {
        strcpy(ret, url);
    }
    return ret;
}

typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realsize + 1);
    if(ptr == NULL) {
        printf("Not enough memory (realloc returned NULL)\n");
        return 0;
    }

    mem->memory = ptr;
    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}

dynArray* processCandleData(const char *jsonData) {
    dynArray* bars = dynArrayMake();

    cJSON *json = cJSON_Parse(jsonData);
    if (json == NULL) {
        printf("Error parsing JSON\n");
        return bars;
    }

    cJSON *timeSeries = cJSON_GetObjectItem(json, "Time Series (1min)");
    if (timeSeries == NULL) {
        printf("Error: No time series data found\n");
        cJSON_Delete(json);
        return bars;
    }

    cJSON *timestamp = NULL;
    cJSON_ArrayForEach(timestamp, timeSeries) {
        cJSON *open = cJSON_GetObjectItem(timestamp, "1. open");
        cJSON *high = cJSON_GetObjectItem(timestamp, "2. high");
        cJSON *low = cJSON_GetObjectItem(timestamp, "3. low");
        cJSON *close = cJSON_GetObjectItem(timestamp, "4. close");
        cJSON *volume = cJSON_GetObjectItem(timestamp, "5. volume");

        if (open && high && low && close && volume) {
            bar *newBar = malloc(sizeof(bar));
            if (newBar == NULL) {
                printf("Error: Could not allocate memory for bar\n");
                continue;
            }

            newBar->open = atof(open->valuestring);
            newBar->high = atof(high->valuestring);
            newBar->low = atof(low->valuestring);
            newBar->close = atof(close->valuestring);
            newBar->volume = atof(volume->valuestring);

            dynArrayAddElement_private(bars, &newBar, sizeof(bar*));
        }
    }

    cJSON_Delete(json);
    return bars;
}

char* get_candles(char* url) {
    CURL *curl;
    CURLcode res;
    MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;

    if (chunk.memory == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    curl_global_init(CURL_GLOBAL_ALL);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
                  curl_easy_strerror(res));
     
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();

    return chunk.memory;
}

void printBars(dynArray* bars) {
    for (size_t i = 0; i < bars->elementsNum; i++) {
        bar* b = *(bar**)dynArrayGetElement(bars, i);
        printf("Bar %zu: Open: %f, High: %f, Low: %f, Close: %f, Volume: %f\n",
               i, b->open, b->high, b->low, b->close, b->volume);
    }
}

void testFunc() {
    interval interval = ONEMIN;
    char *testUrl = makeApiCallUrl(REFRESH_LIST_INTRADAY, interval, "IBM", "RE6GIKKZ0EQJIOMG");

    char* jsonData = get_candles(testUrl);

    if (jsonData != NULL) {
        printf("Received JSON data:\n%s\n", jsonData);

        dynArray* bars = processCandleData(jsonData);

        printBars(bars);

        free(jsonData);
        for (size_t i = 0; i < bars->elementsNum; i++) {
            bar* b = *(bar**)dynArrayGetElement(bars, i);
            free(b);
        }
        free(bars);
    } else {
        printf("Failed to retrieve data\n");
    }

    free(testUrl);
}
