#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

#include "dynArray.h"

// RE6GIKKZ0EQJIOMG - апи ключ

// struct that have data of bar
typedef struct {
    float open;
    float high;
    float low;
    float close;
    float volume;
} bar;

// one of possible intervals of bar
typedef enum { 
    ONEMIN,
    FIVEMIN,
    FIVETEENMIN, 
    HALFOFHOUR, 
    HOUR
}interval;

typedef enum {
    REFRESH_LIST_INTRADAY,
    SEARCH_BAR
}apiCallAction;

/*
 * returns array of bars from json input
 */
dynArray processCandleData(const char *jsonData) {


}

char* getIntervalString(interval interval) {
    switch(interval) {
        case ONEMIN:
            return "1min";
        case FIVEMIN:
            return "5min";
        case FIVETEENMIN:
            return "15min";
        case HALFOFHOUR:
            return "30min";
        case HOUR:
            return "60min";
    }
}
char* makeApiCallUrl(apiCallAction act,
                   interval interval,
                   char* symbol,
                   char* apikey) {

    // https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=5min&apikey=demo need
    // https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=IBM&interval=ONEMIN&apikey=RE6GIKKZ0EQJIOMG got

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

    char *ret = malloc( sizeof(char) * strlen(url) );

    for (int i = 0; i < strlen(url); ++i)
    {
        ret[i] = url[i];
    }
    return ret;
    // url[strlen(url)] = '\0';
}

char* callApi(char* url) {

}

dynArray getCandels(interval interval, int candels_num, char* symbol) {
    // char* url = makeApiCallUrl(REFRESH_LIST, interval, symbol, );
}

void testFunc() {
    interval interval = ONEMIN;
    char *testchar = makeApiCallUrl(REFRESH_LIST_INTRADAY, interval, "IBM", "RE6GIKKZ0EQJIOMG");
    printf("\n some %s\n", testchar);

    CURL *curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, testchar);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

    /* cache the CA cert bundle in memory for a week */
    curl_easy_setopt(curl, CURLOPT_CA_CACHE_TIMEOUT, 604800L);

    /* Perform the request, res gets the return code */
    res = curl_easy_perform(curl);

    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
}

















