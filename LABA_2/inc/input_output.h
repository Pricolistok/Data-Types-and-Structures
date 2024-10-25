#ifndef INPUT_OUTPUT_H__

#define INPUT_OUTPUT_H__

#include <stdio.h>
#include "struct.h"

int add_to_file(char **argv, size_t *cnt_data_in_file);
int input_in_file_one_elem(FILE *file_out, int cnt, size_t len_arr);
int read_to_arr(char **argv, show_info arr_show_info[], size_t *len_arr_show_info);
int read_item(FILE *file_in, show_info arr_show_info[], size_t cnt_elems_arr);
void create_arr_keys(show_info arr_show_info[], key_index arr_key_index[], size_t len_arr_show_info);
void work_with_errors(int rc);
void clean_enter();
int input_data_from_array(char **argv, show_info arr_show_info[], size_t len_arr_show_info);
int check_file(char **argv);
void choose_menu(int *menu);
void print_elem_show(size_t id, char name_theater[], char name_show[], double start_price, double finish_price, char type_of_show[], char name_composer[], char country[], char type_of_musicial[], char start_age[], char duration[]);
void print_header_arr_show();
void print_elem_keys(size_t id, double start_price);
void print_header_keys();
void print_header_analysys();
void print_elem_analisys(size_t len_arr, unsigned long long buble_sort_show, unsigned long long qsort_time_show, unsigned long long buble_sort_key, unsigned long long qsort_time_key);
void print_elem_analisys_percent(size_t len_arr, double buble_sort_show, double qsort_time_show, double buble_sort_key, double qsort_time_key);

#endif
