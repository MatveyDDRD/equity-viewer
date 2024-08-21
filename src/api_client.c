#include <stdio.h>
#include <curl/curl.h>
#include <string.h>

#include "dynArray.h"

// RE6GIKKZ0EQJIOMG - апи ключ (не знаю работает или нет)

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
    NONE,
    ONEMIN,
    FIVEMIN,
    FIVETEENMIN, 
    HALFOFHOUR, 
    HOUR
}interval;

/*
 * returns array of bars from json input
 */
dynArray processCandleData(const char *jsonData) {


}



dynArray get_candels(interval interval, int candels_num)
{

}