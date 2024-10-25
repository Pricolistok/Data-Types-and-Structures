#ifndef STRUCT_H__

#define STRUCT_H__

#include "consts.h"

typedef struct
{
    char name_theater[LEN_NAME_THEATER];
    char name_show[LEN_NAME_SHOW];
    double start_price;
    double finish_price;
    int type_of_show;
    union{
        unsigned int age_start;
        struct 
        {
            char name_composer[LEN_NAME_COMPOSER];
            char country[LEN_COUNTRY];
            int type_of_musical;
            int age_start;
            int duration;
        } add_character;
    } character;
} show_info;

typedef struct 
{
    int index;
    double start_price;
} key_index;

#endif
