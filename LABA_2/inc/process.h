#ifndef PROCESS_H__

#define PROCESS_H__

#include <stdio.h>
#include "struct.h"

void change_elems_arr_struct_show(show_info arr_show_info[], size_t index_1, size_t index_2);
void change_elems_arr_struct_keys(key_index arr_key_indexes[], size_t index_1, size_t index_2);
int remove_element(show_info arr_show_info[], key_index arr_key_index[], size_t *len_arr_show_info);
void setting_arr_key(key_index arr_key_index[], size_t len_arr_show_info);
int find_elem(show_info arr_show_info[], size_t len_arr_show_info);
void print_all(show_info arr_show_info[], size_t len_arr_show_info);
void sort_arr_show_info(show_info arr_show_info[], size_t len_arr_show_info);
void sort_arr_key_index(key_index arr_key_index[], size_t len_arr_show_info);
void print_one_elem(show_info arr_show_info[], size_t i);
void print_all_elems_with_keys(show_info arr_show_info[], key_index arr_key_index[], size_t len_arr_show_info);
int compare_index_keys(const void *a, const void *b);
int compare_show_arr(const void *a, const void *b);
void analisys_time_sort_one_size(char **argv, key_index arr_key_index[], show_info arr_show_info[], size_t len_arr, size_t len_arr_show_info);
int analysys_all_sizes(char **argv, key_index arr_key_index[], show_info arr_show_info[], size_t len_arr_show_info);

#endif
