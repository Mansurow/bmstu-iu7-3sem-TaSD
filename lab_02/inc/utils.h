#ifndef _UTILS_H
#define _UTILS_H

#define STRING_MAIN    1001
#define STRING_COUNTRY 61
#define STRING_CAPITAL 41
#define STRING_MATERIC 37
#define STRING_BUFF    400
#define STRING_SPORT   51
#define STRING_OBJECTS 51

#define NUMBER_MATERIC   6
#define NUMBER_TOURISM   3
#define NUMBER_COUNTRY 300

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

typedef struct
{
    unsigned int number_objects;
    char name_object[STRING_OBJECTS];
} st_sightseeing;
typedef struct
{
    unsigned short main_season;
    short air_temperature;
    short water_temperature;
    unsigned short time_flying;
} st_beach;
typedef struct
{
    char kind_sport[STRING_SPORT];
    unsigned long int min_count_price;
} st_sport;
typedef struct
{
    _Bool tourism_sightseeing;
    _Bool tourism_beach;
    _Bool tourism_sport;
    union un_kid_toutism
    {
        st_sightseeing sightseeing;
        st_beach beach;
        st_sport sport;
    } kid_tourism;
} st_tourism;
typedef struct
{
    struct st_main_data_country
    {
        char name_country[STRING_COUNTRY];
        char capital[STRING_CAPITAL];
        char materic[STRING_MATERIC];
        long int population;
    } main_data;
    _Bool covid_tests;
    st_tourism tourism;

} st_travel;
typedef struct {
    int index;
    char name_country[STRING_COUNTRY];
} st_key_travel;

#endif //_UTILS_H