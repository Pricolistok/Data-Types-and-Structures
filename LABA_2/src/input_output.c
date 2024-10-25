#include <string.h>
#include "consts.h"
#include "errors.h"
#include "input_output.h"
#include "struct.h"

void clean_enter()
{
    while (getchar() != '\n');
}

int input_in_file_one_elem(FILE *file_out, int cnt, size_t len_arr)
{
    int rc;
    char name_theater[LEN_NAME_THEATER + CHECK_CONST];
    char name_show[LEN_NAME_SHOW + CHECK_CONST];
    char name_of_composer[LEN_NAME_COMPOSER + CHECK_CONST];
    char country[LEN_COUNTRY + CHECK_CONST];
    double start_price, finish_price;
    int type_of_show;
    int age_start;
    int type_of_musical;
    int duration;
    int stop_input;
    char start_price_check[LEN_DOUBLE + CHECK_CONST];
    char finish_price_check[LEN_DOUBLE + CHECK_CONST];

    if (cnt != 0)
    {
        printf("Вы хотите завершить ввод?\n0 - Нет\n1 - Да\n");
        printf("Ввод: ");
        rc = scanf("%d", &stop_input);
        if ((rc != 1))
            return ERROR_MENU;
        if (stop_input == 1)
            return STOP_INPUT;
        else if (stop_input != 0)
            return ERROR_MENU;
        clean_enter();
    }

    printf("Введите название театра\n");
    printf("Название до 25 символов\n");
    printf("Ввод: ");
    if (fgets(name_theater, LEN_NAME_THEATER + CHECK_CONST, stdin) == NULL)
        return ERROR_IN_NAME_THEATER;

    name_theater[strlen(name_theater) - 1] = 0;

    if ((strlen(name_theater) > LEN_NAME_THEATER) || (strlen(name_theater) == 0))
    {
        return ERROR_IN_NAME_THEATER;
    }

    printf("Ввведите название шоу\n");
    printf("Название до 25 символов\n");
    printf("Ввод: ");
    if (fgets(name_show, LEN_NAME_SHOW + CHECK_CONST, stdin) == NULL)
        return ERROR_IN_NAME_SHOW;

    name_show[strlen(name_show) - 1] = 0;

    if ((strlen(name_show) > LEN_NAME_SHOW) || (strlen(name_show) == 0))
    {
        return ERROR_IN_NAME_SHOW;
    }

    printf("Введите минимальную цену билета в рублях\n");
    printf("Длина до 16 символов\n");
    printf("Ввод: ");
    rc = scanf("%lf", &start_price);
    if (rc != 1)
        return ERROR_START_PRICE;
    if (start_price < 0)
        return ERROR_START_PRICE;
    snprintf(start_price_check, LEN_DOUBLE + CHECK_CONST, "%lf", start_price);
    if (strlen(start_price_check) > 16)
        return ERROR_START_PRICE;
    clean_enter();

    printf("Введите максимальную цену билета в рублях\n");
    printf("Длина до 16 символов\n");
    printf("Ввод: ");
    rc = scanf("%lf", &finish_price);
    if (rc != 1)
        return ERROR_FINISH_PRICE;
    if (finish_price < 0)
        return ERROR_FINISH_PRICE;
    snprintf(finish_price_check, LEN_DOUBLE + CHECK_CONST, "%lf", finish_price);
    if (strlen(finish_price_check) > 16)
        return ERROR_FINISH_PRICE;

    if (finish_price < start_price)
        return ERROR_PRICE;

    clean_enter();

    printf("Введите тип шоу:\n1 - Пьесса \n2 - Драма \n3 - Комедия \n4 - Сказка \n5 - Музыкальный\n");
    printf("Ввод: ");
    rc = scanf("%d", &type_of_show);
    if ((rc != 1) && ((type_of_show < 1) || (type_of_show > 5)))
        return ERROR_TYPE_OF_SHOW;
    if (type_of_show < 0)
        return ERROR_TYPE_OF_SHOW;
    clean_enter();

    if (type_of_show == FAIRY)
    {
        printf("Введите минимальный возраст\n");
        printf("1 - 3+\n 2 - 6+\n 3 - 16+\n");
        printf("Ввод: ");
        rc = scanf("%d", &age_start);
        if (rc != 1)
            return ERROR_IN_AGE_START;
        if ((age_start < 0) && ((age_start != THREE_AGE) || (age_start != SIX_AGE) || (age_start != THREE_AGE)))
            return ERROR_IN_AGE_START;
        clean_enter();
    }
    else if (type_of_show == MUSICIAL)
    {
        printf("Введите имя композитора\n");
        printf("Имя до 25 символов\n");
        printf("Ввод: ");
        if (fgets(name_of_composer, LEN_NAME_COMPOSER + CHECK_CONST, stdin) == NULL)
            return ERROR_IN_COMPOSER;

        name_of_composer[strlen(name_of_composer) - 1] = 0;

        if ((strlen(name_of_composer) > LEN_NAME_COMPOSER) || (strlen(name_of_composer) == 0))
        {
            return ERROR_IN_COMPOSER;
        }

        printf("Введите страну: ");
        printf("Страна до 25 символов\n");
        if (fgets(country, LEN_COUNTRY + CHECK_CONST, stdin) == NULL)
            return ERROR_IN_COUNTRY;

        country[strlen(country) - 1] = 0;

        if ((strlen(country) > LEN_COUNTRY) || (strlen(country) == 0))
        {
            return ERROR_IN_COUNTRY;
        }

        printf("Введите тип:\n1 - Баллет \n2 - Опера \n3 - Мюзикл\n");
        printf("Ввод: ");
        rc = scanf("%d", &type_of_musical);
        if ((rc != 1) || (type_of_musical < 1) || (type_of_musical > 3))
            return ERROR_IN_TYPE_OF_MUSIC;
        if (type_of_musical < 0)
            return ERROR_IN_TYPE_OF_MUSIC;
        clean_enter();

        printf("Введите минимальный возраст\n");
        printf("1 - 3+\n 2 - 6+\n 3 - 16+\n");
        printf("Ввод: ");
        rc = scanf("%d", &age_start);
        if (rc != 1)
            return ERROR_IN_AGE_START;
        if ((age_start < 0) && ((age_start != THREE_AGE) || (age_start != SIX_AGE) || (age_start != SIXTEEN_AGE)))
            return ERROR_IN_AGE_START;
        clean_enter();

        printf("Введите продолжительность в минутах\n");
        printf("Ввод: ");
        rc = scanf("%d", &duration);
        if ((rc != 1) || (duration < 1))
            return ERROR_IN_DURATION;
        if (duration < 0)
            return ERROR_IN_DURATION;
        clean_enter();
    }
    if (len_arr != 0)
        fprintf(file_out, "\n");
    fprintf(file_out, "%s", name_theater);
    fprintf(file_out, "%s", name_show);
    fprintf(file_out, "%lf\n", start_price);
    fprintf(file_out, "%lf\n", finish_price);
    fprintf(file_out, "%d", type_of_show);
    if (type_of_show == 4)
    {
        fprintf(file_out, "\n");
        fprintf(file_out, "%d", age_start);
    }
    else if (type_of_show == 5)
    {
        fprintf(file_out, "\n");
        fprintf(file_out, "%s", name_of_composer);
        fprintf(file_out, "%s", country);
        fprintf(file_out, "%d\n", type_of_musical);
        fprintf(file_out, "%d\n", age_start);
        fprintf(file_out, "%d", duration);
    }
    return OK;
}

int add_to_file(char **argv, size_t *cnt_data_in_file)
{
    int rc;
    int cnt = 0;
    char rubbish[LEN_RUBBISH];
    FILE *file_out = fopen(argv[1], "a");

    if (file_out == NULL)
        return ERROR_OPEN_FILE;

    fseek(file_out, 0, SEEK_END);
    
    if (*cnt_data_in_file >= LEN_STRUCT_ARR)
        return ERROR_MAXI_ELEMS;

    while (*cnt_data_in_file < LEN_STRUCT_ARR)
    {
        rc = input_in_file_one_elem(file_out, cnt, *cnt_data_in_file);
        if (rc == ERROR_MENU)
        {
            printf("Ошибка ввода!\n");
            fgets(rubbish, LEN_RUBBISH, stdin);
            break;
        }
        else if (rc == STOP_INPUT)
        {
            printf("Ввод окончен!\n");
            break;
        }
        else if (rc != OK)
        {
            work_with_errors(rc);
            fgets(rubbish, LEN_RUBBISH, stdin);
            break;
        }
        cnt++;
        *cnt_data_in_file = *cnt_data_in_file + 1;
    }
    fclose(file_out);
    return OK;
}

int read_item(FILE *file_in, show_info arr_show_info[], size_t cnt_elems_arr)
{
    int rc;
    char name_theater[LEN_NAME_THEATER + CHECK_CONST];
    char name_show[LEN_NAME_SHOW + CHECK_CONST];
    char name_of_composer[LEN_NAME_COMPOSER + CHECK_CONST];
    char country[LEN_COUNTRY + CHECK_CONST];
    double start_price, finish_price;
    int type_of_show;
    int age_start;
    int type_of_musical;
    int duration;
    char start_price_check[LEN_DOUBLE + CHECK_CONST];
    char finish_price_check[LEN_DOUBLE + CHECK_CONST];

    if (fgets(name_theater, LEN_NAME_THEATER + CHECK_CONST, file_in) == NULL)
        return ERROR_IN_NAME_THEATER;
    name_theater[strlen(name_theater) - 1] = 0;
    if ((strlen(name_theater) > LEN_NAME_THEATER) || (strlen(name_theater) == 0))
        return ERROR_IN_NAME_THEATER;

    if (fgets(name_show, LEN_NAME_SHOW + CHECK_CONST, file_in) == NULL)
        return ERROR_IN_NAME_SHOW;
    name_show[strlen(name_show) - 1] = 0;
    if ((strlen(name_show) > LEN_NAME_SHOW) || (strlen(name_show) == 0))
        return ERROR_IN_NAME_SHOW;

    rc = fscanf(file_in, "%lf", &start_price);
    if (rc != 1)
        return ERROR_START_PRICE;
    if (start_price < 0)
        return ERROR_START_PRICE;
    snprintf(start_price_check, LEN_DOUBLE + CHECK_CONST, "%lf", start_price);
    if (strlen(start_price_check) > 16)
        return ERROR_START_PRICE;
    fgetc(file_in);

    rc = fscanf(file_in, "%lf", &finish_price);
    if (rc != 1)
        return ERROR_FINISH_PRICE;
    if (finish_price < 0)
        return ERROR_FINISH_PRICE;
    snprintf(finish_price_check, LEN_DOUBLE + CHECK_CONST, "%lf", finish_price);
    if (strlen(finish_price_check) > 16)
        return ERROR_FINISH_PRICE;
    fgetc(file_in);

    if (finish_price < start_price)
        return ERROR_PRICE;

    rc = fscanf(file_in, "%d", &type_of_show);
    if (rc != 1)
        return ERROR_TYPE_OF_SHOW;
    if (type_of_show < 0)
        return ERROR_TYPE_OF_SHOW;
    fgetc(file_in);

    if (type_of_show == FAIRY)
    {
        rc = fscanf(file_in, "%d", &age_start);
        if (rc != 1)
            return ERROR_IN_AGE_START;
        if ((age_start < 0) && ((age_start != THREE_AGE) || (age_start != SIX_AGE) || (age_start != SIXTEEN_AGE)))
            return ERROR_IN_AGE_START;
        fgetc(file_in);
    }
    else if (type_of_show == MUSICIAL)
    {
        if (fgets(name_of_composer, LEN_NAME_SHOW + CHECK_CONST, file_in) == NULL)
            return ERROR_IN_COMPOSER;
        name_of_composer[strlen(name_of_composer) - 1] = 0;
        if ((strlen(name_of_composer) > LEN_NAME_COMPOSER) || (strlen(name_of_composer) == 0))
            return ERROR_IN_COMPOSER;

        if (fgets(country, LEN_COUNTRY + CHECK_CONST, file_in) == NULL)
            return ERROR_IN_COUNTRY;
        country[strlen(country) - 1] = 0;
        if ((strlen(country) > LEN_COUNTRY) || (strlen(country) == 0))
            return ERROR_IN_COUNTRY;

        rc = fscanf(file_in, "%d", &type_of_musical);
        if (rc != 1)
            return ERROR_IN_TYPE_OF_MUSIC;
        if (type_of_musical < 0)
            return ERROR_IN_TYPE_OF_MUSIC;
        fgetc(file_in);

        rc = fscanf(file_in, "%d", &age_start);
        if (rc != 1)
            return ERROR_IN_AGE_START;
        if ((age_start < 0) && ((age_start != THREE_AGE) || (age_start != SIX_AGE) || (age_start != SIXTEEN_AGE)))
            return ERROR_IN_AGE_START;
        fgetc(file_in);
        
        rc = fscanf(file_in, "%d", &duration);
        if (rc != 1)
            return ERROR_IN_DURATION;
        if (duration < 0)
            return ERROR_IN_DURATION;
        fgetc(file_in);
    }

    strcpy(arr_show_info[cnt_elems_arr].name_theater, name_theater);
    strcpy(arr_show_info[cnt_elems_arr].name_show, name_show);
    arr_show_info[cnt_elems_arr].start_price = start_price;
    arr_show_info[cnt_elems_arr].finish_price = finish_price;
    arr_show_info[cnt_elems_arr].type_of_show = type_of_show;
    if (type_of_show == 4)
        arr_show_info[cnt_elems_arr].character.age_start = age_start;
    else if (type_of_show == 5)
    {
        strcpy(arr_show_info[cnt_elems_arr].character.add_character.name_composer, name_of_composer);
        strcpy(arr_show_info[cnt_elems_arr].character.add_character.country, country);
        arr_show_info[cnt_elems_arr].character.add_character.type_of_musical = type_of_musical;
        arr_show_info[cnt_elems_arr].character.add_character.age_start = age_start;
        arr_show_info[cnt_elems_arr].character.add_character.duration = duration;
    }
    return OK;
}

int read_to_arr(char **argv, show_info arr_show_info[], size_t *len_arr_show_info)
{
    int rc;
    size_t cnt_elems_arr = 0;
    FILE *file_in = fopen(argv[1], "r");

    if (file_in == NULL)
        return ERROR_OPEN_FILE;

    while (!feof(file_in))
    {
        if (cnt_elems_arr > LEN_STRUCT_ARR)
            return ERROR_LEN_ARR;
        rc = read_item(file_in, arr_show_info, cnt_elems_arr);
        if (rc != OK)
        {
            return rc;
        }
        cnt_elems_arr++;
    }
    *len_arr_show_info = cnt_elems_arr;
    fclose(file_in);
    return OK;
}

void create_arr_keys(show_info arr_show_info[], key_index arr_key_index[], size_t len_arr_show_info)
{
    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        arr_key_index[i].index = i;
        arr_key_index[i].start_price = arr_show_info[i].start_price;
    }
}

int check_file(char **argv)
{
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
        return ERROR_OPEN_FILE;
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
        return ZERO_ELEMS;
    return OK;
}

void work_with_errors(int rc)
{
    switch (rc)
    {
    case ERROR_OPEN_FILE:
        printf("Ошибка открытия файла!\n");
        break;

    case ERROR_LEN_ARR:
        printf("Ошибка количества структур!\n");
        break;

    case ERROR_IN_NAME_THEATER:
        printf("Ошибка при введениии названии театра!\n");
        break;

    case ERROR_IN_NAME_SHOW:
        printf("Ошибка при введениии названии спектакля!\n");
        break;

    case ERROR_START_PRICE:
        printf("Ошибка при введениии начальной цены!\n");
        break;

    case ERROR_FINISH_PRICE:
        printf("Ошибка при введениии конечной цены!\n");
        break;

    case ERROR_TYPE_OF_SHOW:
        printf("Ошибка при введении жанра шоу!\n");
        break;

    case ERROR_IN_COMPOSER:
        printf("Ошибка при введении имени композитора\n");
        break;

    case ERROR_IN_COUNTRY:
        printf("Ошибка при введении страны\n");
        break;

    case ERROR_IN_TYPE_OF_MUSIC:
        printf("Ошибка при вводе музыкального жанра!\n");
        break;

    case ERROR_IN_AGE_START:
        printf("Ошибка при вводе минимального возраста!\n");
        break;

    case ERROR_IN_DURATION:
        printf("Ошибка при вводе продолжительности!\n");
        break;

    case ERROR_PRICE:
        printf("Минимальная цена больше максимальной!\n");
        break;
    }
}

int input_data_from_array(char **argv, show_info arr_show_info[], size_t len_arr_show_info)
{
    FILE *file_out = fopen(argv[1], "w");
    if (file_out == NULL)
        return ERROR_OPEN_FILE;

    for (size_t i = 0; i < len_arr_show_info; i++)
    {
        if (i != 0)
            fprintf(file_out, "\n");
        fprintf(file_out, "%s\n", arr_show_info[i].name_theater);
        fprintf(file_out, "%s\n", arr_show_info[i].name_show);
        fprintf(file_out, "%lf\n", arr_show_info[i].start_price);
        fprintf(file_out, "%lf\n", arr_show_info[i].finish_price);
        fprintf(file_out, "%d", arr_show_info[i].type_of_show);
        if (arr_show_info[i].type_of_show == 4)
        {
            fprintf(file_out, "\n");
            fprintf(file_out, "%d", arr_show_info[i].character.age_start);
        }
        else if (arr_show_info[i].type_of_show == 5)
        {
            fprintf(file_out, "\n");
            fprintf(file_out, "%s\n", arr_show_info[i].character.add_character.name_composer);
            fprintf(file_out, "%s\n", arr_show_info[i].character.add_character.country);
            fprintf(file_out, "%d\n", arr_show_info[i].character.add_character.type_of_musical);
            fprintf(file_out, "%d\n", arr_show_info[i].character.add_character.age_start);
            fprintf(file_out, "%d", arr_show_info[i].character.add_character.duration);
        }
    }
    fclose(file_out);
    return OK;
}

void choose_menu(int *menu)
{
    int rc;
    printf("Что Вы хотите сделать?\n");
    printf("1 - Добавить элементы\n2 - Удалить элемент\n3 - Завершить программу\n4 - Вывести искомые значения\n5 - Вывести всё\n6 - Считать базу данных в массив\n7 - Отсортировать массив с структурами по начальной цене\n8 - Отсортировать массив с ключами по цене\n9 - Сделать замеры\n");
    printf("Ваш выбор: ");
    rc = scanf("%d", menu);
    clean_enter();
    while ((rc != 1) || (*menu > 9) || (*menu < 1))
    {
        printf("Ошибка выбора пункта меню\n");
        printf("Ваш выбор: ");
        rc = scanf("%d", menu);
        clean_enter();
    }
}

void print_elem_show(size_t id, char name_theater[], char name_show[], double start_price, double finish_price, char type_of_show[], char name_composer[], char country[], char type_of_musicial[], char start_age[], char duration[])
{
    printf("|%6zu|%-28s|%-28s|%-16.2f|%-16.2f|%-16s|%-28s|%-28s|%-28s|%-21s|%-21s|\n", id, name_theater, name_show, start_price, finish_price, type_of_show, name_composer, country, type_of_musicial, start_age, duration);
    printf("|------|----------------------------|----------------------------|----------------|----------------|----------------|----------------------------|----------------------------|----------------------------|---------------------|---------------------|\n");
}

void print_header_arr_show()
{
    printf("|------|----------------------------|----------------------------|----------------|----------------|----------------|----------------------------|----------------------------|----------------------------|---------------------|---------------------|\n");
    printf("|  ID  |     Название театра        |       Название шоу         | Начальная цена |  Конечная цена |  Тип спектакля |       Имя композитора      |           Страна           |      Музыкальный жанр      | Минимальный возраст |  Продолжительность  |\n");
    printf("|------|----------------------------|----------------------------|----------------|----------------|----------------|----------------------------|----------------------------|----------------------------|---------------------|---------------------|\n");
}

void print_elem_keys(size_t id, double start_price)
{
    printf("|%6zu|%-16.2f|\n", id, start_price);
    printf("|------|----------------|\n");
}

void print_header_keys()
{
    printf("|------|----------------|\n");
    printf("|  ID  | Начальная цена |\n");
    printf("|------|----------------|\n");
}

void print_header_analysys()
{
    printf("|----------------------|------------------------------|------------------------------|------------------------------|------------------------------|\n");
    printf("|                      | Сортировка пузырьком массива |  Быстрая сортировка массива  | Сортировка пузырьком массива |  Быстрая сортировка массива  |\n");
    printf("| Количесвто элементов |  структур  со всеми данными  |  структур  со всеми данными  |      структур  с ключами     |      структур  с ключами     |\n");
    printf("|                      |          в тиках             |          в тиках             |          в тиках             |          в тиках             |\n");
    printf("|----------------------|------------------------------|------------------------------|------------------------------|------------------------------|\n");
}

void print_elem_analisys(size_t len_arr, unsigned long long buble_sort_show, unsigned long long qsort_time_show, unsigned long long buble_sort_key, unsigned long long qsort_time_key)
{
    printf("|%22zu|%30lld|%30lld|%30lld|%30lld|\n", len_arr, buble_sort_show, qsort_time_show, buble_sort_key, qsort_time_key);
    printf("|----------------------|------------------------------|------------------------------|------------------------------|------------------------------|\n");
}

void print_elem_analisys_percent(size_t len_arr, double buble_sort_show, double qsort_time_show, double buble_sort_key, double qsort_time_key)
{
    printf("|                                                          Процентное соотношение                                                                  |\n");
    printf("|----------------------|------------------------------|------------------------------|------------------------------|------------------------------|\n");
    printf("|%22zu|%+29.2f%%|%+29.2f%%|%+29.2f%%|%+29.2f%%|\n", len_arr, buble_sort_show, qsort_time_show, buble_sort_key, qsort_time_key);
    printf("|----------------------|------------------------------|------------------------------|------------------------------|------------------------------|\n");
    printf("\n\n");
}
