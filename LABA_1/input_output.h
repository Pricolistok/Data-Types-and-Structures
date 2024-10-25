// Файл хранящий в себе заголовки функций ввода и вывода
#ifndef INPUT_OUTPUT_H__

#define INPUT_OUTPUT_H__

#include "struct.h"

int input_float_arr(valid_numbers *number, size_t *len_num_int, size_t *len_num_float);
int input_symbols(char num[LEN_MANTISSA + 3], size_t len_num, int code);
int check_elem_float(char saver_full_number[LEN_MANTISSA + 3], char mantissa_saver_integer[LEN_MANTISSA + 2], char mantissa_saver_float[LEN_MANTISSA + 2], int *flag, size_t *len_float, size_t *len_int);
int input_order(valid_numbers *number);
int input_integer_arr(int integer_arr[], size_t *len_num_int, int *sign);
int write_elem_integer(char saver_full_number[LEN_MANTISSA], int integer_arr[LEN_MANTISSA], size_t *len_int, int *flag);
int print_result(valid_numbers *number, int arr_result[LEN_MANTISSA], size_t *len_res_arr, int sign_int, int cnt_zero);
void round_arr(int arr_result[LEN_MANTISSA], size_t *len_res_arr);

#endif
