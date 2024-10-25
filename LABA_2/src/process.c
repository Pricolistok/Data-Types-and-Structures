#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <x86gprintrin.h>
#include <time.h>
#include "consts.h"
#include "errors.h"
#include "input_output.h"
#include "process.h"

void change_elems_arr_struct_show(show_info arr_show_info[], size_t index_1, size_t index_2)
{
    show_info tmp_arr_show;

    tmp_arr_show = arr_show_info[index_1];
    arr_show_info[index_1] = arr_show_info[index_2];
    arr_show_info[index_2] = tmp_arr_show;
}

void change_elems_arr_struct_keys(key_index arr_key_indexes[], size_t index_1, size_t index_2)
{
    key_index tmp;

    tmp = arr_key_indexes[index_1];
    arr_key_indexes[index_1] = arr_key_indexes[index_2];
    arr_key_indexes[index_2] = tmp;
}

int remove_element(show_info arr_show_info[], key_index arr_key_index[], size_t *len_arr_show_info)
{
    int rc;
    int flag = 0;
    int cnt = 0;
    char name_show[LEN_NAME_SHOW + CHECK_CONST];
    printf("Введите название спектакля, которое хотите удалить\n");
    printf("Название до 25 символов\n");
    printf("Ввод: ");
    if (fgets(name_show, LEN_NAME_SHOW + CHECK_CONST, stdin) == NULL)
        return ERROR_IN_NAME_SHOW;

    name_show[strlen(name_show) - 1] = 0;

    if ((strlen(name_show) > LEN_NAME_SHOW) || (strlen(name_show) == 0))
        return ERROR_IN_NAME_SHOW;

    printf("Сколько записей с данным именем Вы хотите удалит?\n");
    printf("Целое число до 16 символов\n");
    printf("Ввод: ");
    rc = scanf("%d", &flag);
    if (rc != 1)
        return ERROR_REMOVE_ELEM;
    if (flag < 0)
        return ERROR_REMOVE_ELEM;
    clean_enter();

    for (size_t i = 0; i < *len_arr_show_info; i++)
    {
        if ((strcmp(arr_show_info[i].name_show, name_show) == 0) && (cnt < flag))
        {
            for (size_t j = i; j < *len_arr_show_info - 1; j++)
            {
                change_elems_arr_struct_show(arr_show_info, j, j + 1);
                change_elems_arr_struct_keys(arr_key_index, j, j + 1);
            }
            cnt++;
            *len_arr_show_info = *len_arr_show_info - 1;
            i--;
        }
    }
    return OK;
}

void setting_arr_key(key_index arr_key_index[], size_t len_arr_show_info)
{
    for (size_t i = 0; i < len_arr_show_info; i++)
        arr_key_index[i].index = i;
}

void print_one_elem(show_info arr_show_info[], size_t i)
{
    char name_theater[LEN_NAME_THEATER];
    char name_show[LEN_NAME_SHOW];
    double start_price;
    double finish_price;
    char type_of_show[LEN_TYPE_OF_SHOW];
    char name_composer[LEN_NAME_COMPOSER];
    char country[LEN_COUNTRY];
    char type_of_musicial[LEN_TYPE_OF_MUSIC];
    char age_start[LEN_AGE];
    char duration[LEN_DURATION];

    strcpy(name_theater, arr_show_info[i].name_theater);
    strcpy(name_show, arr_show_info[i].name_show);
    start_price = arr_show_info[i].start_price;
    finish_price = arr_show_info[i].finish_price;

    switch (arr_show_info[i].type_of_show)
    {
    case PLAY:
        strcpy(type_of_show, "Piessa\0");
        strcpy(name_composer, "-\0");
        strcpy(country, "-\0");
        strcpy(type_of_musicial, "-\0");
        strcpy(age_start, "-\0");
        strcpy(duration, "-");
        break;

    case DRAMA:
        strcpy(type_of_show, "Dramma\0");
        strcpy(name_composer, "-\0");
        strcpy(country, "-\0");
        strcpy(type_of_musicial, "-\0");
        strcpy(age_start, "-\0");
        strcpy(duration, "-");
        break;

    case COMEDY:
        strcpy(type_of_show, "Comedy\0");
        strcpy(name_composer, "-\0");
        strcpy(country, "-\0");
        strcpy(type_of_musicial, "-\0");
        strcpy(age_start, "-\0");
        strcpy(duration, "-");
        break;

    case FAIRY:
        strcpy(type_of_show, "Fairy\0");
        strcpy(name_composer, "-\0");
        strcpy(country, "-\0");
        switch (arr_show_info[i].character.age_start)
        {
        case THREE_AGE:
            strcpy(age_start, "3+\0");
            break;

        case SIX_AGE:
            strcpy(age_start, "6+\0");
            break;

        case SIXTEEN_AGE:
            strcpy(age_start, "16+\0");
            break;
        }
        strcpy(type_of_musicial, "-\0");
        strcpy(duration, "-");
        break;

    case MUSICIAL:
        strcpy(type_of_show, "Musicial\0");
        strcpy(name_composer, arr_show_info[i].character.add_character.name_composer);
        strcpy(country, arr_show_info[i].character.add_character.country);
        switch (arr_show_info[i].character.add_character.type_of_musical)
        {
        case BALET:
            strcpy(type_of_musicial, "Balet\0");
            break;

        case OPERA:
            strcpy(type_of_musicial, "Opera\0");
            break;

        case MUSICIAL_NAME:
            strcpy(type_of_musicial, "Musicial\0");
            break;
        }
        switch (arr_show_info[i].character.add_character.age_start)
        {
        case THREE_AGE:
            strcpy(age_start, "3+\0");
            break;

        case SIX_AGE:
            strcpy(age_start, "6+\0");
            break;

        case SIXTEEN_AGE:
            strcpy(age_start, "16+\0");
            break;
        }
        snprintf(duration, LEN_DURATION, "%d", arr_show_info[i].character.add_character.duration);
        break;
    }
    print_elem_show(i, name_theater, name_show, start_price, finish_price, type_of_show, name_composer, country, type_of_musicial, age_start, duration);
}

int find_elem(show_info arr_show_info[], size_t len_arr_show_info)
{
    int rc;
    int age_inp;
    int duration_inp;
    int cnt = 0;

    printf("Введите возраст\n");
    printf("1 - 3+\n2 - 6+\n3 - 16+\n");
    printf("Ввод: ");
    rc = scanf("%d", &age_inp);
    if ((rc != 1) || (age_inp > 3) || (age_inp < 1))
        return ERROR_IN_AGE_START;
    if (age_inp < 0)
        return ERROR_IN_AGE_START;
    clean_enter();

    printf("Введите максимальную продолжительность\n");
    printf("Необходимо ввести целое число\n");
    printf("Ввод: ");
    rc = scanf("%d", &duration_inp);
    if (rc != 1)
    {
        clean_enter();
        return ERROR_IN_DURATION;
    }
    if (duration_inp < 0)
    {
        clean_enter();
        return ERROR_IN_DURATION;
    }
    clean_enter();

    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        if ((arr_show_info[i].type_of_show == MUSICIAL) && (arr_show_info[i].character.add_character.type_of_musical == BALET) &&
            (arr_show_info[i].character.add_character.duration < duration_inp) && (arr_show_info[i].character.add_character.age_start == age_inp))
        {
            if (cnt == 0)
                print_header_arr_show();
            cnt++;
            print_one_elem(arr_show_info, i);
        }
    }
    if (cnt == 0)
        return ZERO_ELEMS;
    return OK;
}

void print_all(show_info arr_show_info[], size_t len_arr_show_info)
{
    int cnt = 0;

    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        if (cnt == 0)
            print_header_arr_show();
        cnt++;
        print_one_elem(arr_show_info, i);
    }
}

void sort_arr_show_info(show_info arr_show_info[], size_t len_arr_show_info)
{
    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        for (size_t j = 0; j < len_arr_show_info - i - 1; j++)
        {
            if (arr_show_info[j].start_price > arr_show_info[j + 1].start_price)
                change_elems_arr_struct_show(arr_show_info, j, j + 1);
        }
    }
}

void sort_arr_key_index(key_index arr_key_index[], size_t len_arr_show_info)
{
    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        for (size_t j = 0; j < len_arr_show_info - i - 1; j++)
        {
            if (arr_key_index[j].start_price > arr_key_index[j + 1].start_price)
                change_elems_arr_struct_keys(arr_key_index, j, j + 1);
        }
    }
}

void print_all_elems_with_keys(show_info arr_show_info[], key_index arr_key_index[], size_t len_arr_show_info)
{
    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        if (i == 0)
            print_header_arr_show();
        print_one_elem(arr_show_info, arr_key_index[i].index);
    }
    printf("Таблица ключей\n");
    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        if (i == 0)
            print_header_keys();
        print_elem_keys(arr_key_index[i].index, arr_key_index[i].start_price);
    }
}

int compare_show_arr(const void *a, const void *b)
{
    // Приводим указатели к типу show_info
    show_info *show_1 = (show_info *)a;
    show_info *show_2 = (show_info *)b;

    // Сравниваем поля start_price
    if (show_1->start_price < show_2->start_price)
        return -1;
    if (show_1->start_price > show_2->start_price)
        return 1;
    return 0;
}

int analysys_all_sizes(char **argv, key_index arr_key_index[], show_info arr_show_info[], size_t len_arr_show_info)
{
    if (len_arr_show_info < 1000)
        return ERROR_ANALIS;
    size_t len_arr = LEN_ARR_5;
    read_to_arr(argv, arr_show_info, &len_arr_show_info);
    create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
    analisys_time_sort_one_size(argv, arr_key_index, arr_show_info, len_arr, len_arr_show_info);

    len_arr = LEN_ARR_50;
    read_to_arr(argv, arr_show_info, &len_arr_show_info);
    create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
    analisys_time_sort_one_size(argv, arr_key_index, arr_show_info, len_arr, len_arr_show_info);

    len_arr = LEN_ARR_100;
    read_to_arr(argv, arr_show_info, &len_arr_show_info);
    create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
    analisys_time_sort_one_size(argv, arr_key_index, arr_show_info, len_arr, len_arr_show_info);

    len_arr = LEN_ARR_500;
    read_to_arr(argv, arr_show_info, &len_arr_show_info);
    create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
    analisys_time_sort_one_size(argv, arr_key_index, arr_show_info, len_arr, len_arr_show_info);

    len_arr = LEN_ARR_1000;
    read_to_arr(argv, arr_show_info, &len_arr_show_info);
    create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
    analisys_time_sort_one_size(argv, arr_key_index, arr_show_info, len_arr, len_arr_show_info);

    return OK;
}

void analisys_time_sort_one_size(char **argv, key_index arr_key_index[], show_info arr_show_info[], size_t len_arr, size_t len_arr_show_info)
{
    unsigned long long t_start, t_finish, t_result_my_show = 0, t_result_qsort_show = 0, t_result_my_key = 0, t_result_qsort_key = 0;

    double bubble_show, qsort_show, bubble_key, qsort_key;

    for (size_t i = 0; i < CNT_ALNALYS; i++)
    {
        read_to_arr(argv, arr_show_info, &len_arr_show_info);

        t_start = __rdtsc();
        sort_arr_show_info(arr_show_info, len_arr);
        t_finish = __rdtsc();
        t_result_my_show += t_finish - t_start;

        read_to_arr(argv, arr_show_info, &len_arr_show_info);

        t_start = __rdtsc();
        qsort(arr_show_info, len_arr, sizeof(arr_show_info[0]), compare_show_arr);
        t_finish = __rdtsc();
        t_result_qsort_show += t_finish - t_start;

        read_to_arr(argv, arr_show_info, &len_arr_show_info);

        create_arr_keys(arr_show_info, arr_key_index, len_arr);

        t_start = __rdtsc();
        sort_arr_key_index(arr_key_index, len_arr);
        t_finish = __rdtsc();
        t_result_my_key += t_finish - t_start;

        create_arr_keys(arr_show_info, arr_key_index, len_arr);

        t_start = __rdtsc();
        qsort(arr_key_index, len_arr, sizeof(arr_key_index[0]), compare_index_keys);
        t_finish = __rdtsc();
        t_result_qsort_key += t_finish - t_start;
    }

    print_header_analysys();

    bubble_show = (((double)t_result_qsort_show / (double)CNT_ALNALYS - (double)t_result_my_show / (double)CNT_ALNALYS) / ((double)(t_result_my_show) / (double)CNT_ALNALYS)) * 100;
    qsort_show = (((double)t_result_my_show / (double)CNT_ALNALYS - (double)t_result_qsort_show / (double)CNT_ALNALYS) / ((double)(t_result_qsort_show) / (double)CNT_ALNALYS)) * 100;
    bubble_key = (((double)t_result_qsort_key / (double)CNT_ALNALYS - (double)t_result_my_key / (double)CNT_ALNALYS) / ((double)(t_result_my_key) / (double)CNT_ALNALYS)) * 100;
    qsort_key = (((double)t_result_my_key / (double)CNT_ALNALYS - (double)t_result_qsort_key / (double)CNT_ALNALYS) / ((double)(t_result_qsort_key) / (double)CNT_ALNALYS)) * 100;
    // if (t_result_qsort_show > t_result_my_show)
    // {
    //     qsort_show *= -1;
    //     qsort_key *= -1;
    // }
    print_elem_analisys(len_arr, t_result_my_show / CNT_ALNALYS, t_result_qsort_show / CNT_ALNALYS, t_result_my_key / CNT_ALNALYS, t_result_qsort_key / CNT_ALNALYS);
    print_elem_analisys_percent(len_arr, bubble_show, qsort_show, bubble_key, qsort_key);
    printf("При использовании быстрой сортировки для сортировки массива структур с ключами можно выиграть %+.2lf%% времени, затратив на %.2lf%% памяти больше.\n", (((double)t_result_qsort_show - (double)t_result_qsort_key) / (double)t_result_qsort_show) * 100, (double)sizeof(arr_key_index[0]) / (double)sizeof(arr_show_info[0]) * 100);
    printf("\n");
    printf("При использовании пузырьковой сортировки для сортировки массива структур с ключами можно выиграть %+.2lf%% времени, затратив на %.2lf%% памяти больше.\n", (((double)t_result_my_show - (double)t_result_my_key) / (double)t_result_my_show) * 100, (double)sizeof(arr_key_index[0]) / (double)sizeof(arr_show_info[0]) * 100);
    printf("\n\n");
}

int compare_index_keys(const void *a, const void *b)
{
    // Приводим указатели к типу key_index
    key_index *key_1 = (key_index *)a;
    key_index *key_2 = (key_index *)b;

    // Сравниваем поля start_price
    if (key_1->start_price < key_2->start_price)
        return -1;
    if (key_1->start_price > key_2->start_price)
        return 1;
    return 0;
}
