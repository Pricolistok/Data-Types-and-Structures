// Файл для заголовков всех функций деления
#ifndef PROCESS_H__

#define PROCESS_H__

void substracting(int num[LEN_MANTISSA], int all_float_num[LEN_MANTISSA], int history_arr[LEN_MANTISSA], size_t len_num, size_t *len_hist, size_t checker, int *need_sub);
void write_to_all_num(int all_float_num[], valid_numbers *number, size_t len_num_int, size_t len_num_float, size_t *cursor_save);
void stabilize_nums(int buffer[LEN_MANTISSA * 2], int integer_arr[], size_t len_num_float, size_t len_integer_arr, size_t *cursor);
int separator(valid_numbers *number, int arr_result[LEN_MANTISSA + 1], size_t *len_res_arr, int integer_arr[], size_t len_num_int, size_t len_num_float, size_t len_integer_arr, int *cnt_z);
int cnt_summ(int arr[], size_t len);

#endif
