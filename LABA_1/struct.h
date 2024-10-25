// Файл хранящий структуру данных
#ifndef STRUCT_H__

#define STRUCT_H__

#include "const.h"

// Структура
typedef struct
{
    int sign;
    int mantissa_integer[LEN_MANTISSA];
    int mantissa_float[LEN_MANTISSA];
    int order; 
} valid_numbers;

#endif
