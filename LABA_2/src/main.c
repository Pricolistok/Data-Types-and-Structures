#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "input_output.h"
#include "process.h"
#include "errors.h"

int main(int argc, char **argv)
{
    int rc;
    size_t len_arr_show_info = 0, saver_len_arr = 0;
    show_info arr_show_info[LEN_STRUCT_ARR];
    key_index arr_key_index[LEN_STRUCT_ARR];
    int menu = 0;
    if (argc != 2)
    {
        printf("Ошибка количества аргументов!\n");
        return ERROR_AGS;
    }
    rc = check_file(argv);
    if (rc == ZERO_ELEMS)
    {
        while (rc == ZERO_ELEMS)
        {
            printf("Файл пуст, поэтому его необходимо наполнить!\n");
            saver_len_arr = len_arr_show_info;
            rc = add_to_file(argv, &len_arr_show_info);
            if (rc == ERROR_OPEN_FILE)
            {
                printf("Ошибка открытия файла!\n");
                return ERROR_OPEN_FILE;
            }
            if (saver_len_arr != len_arr_show_info)
            {
                rc = read_to_arr(argv, arr_show_info, &len_arr_show_info);
                if (rc != OK)
                {
                    work_with_errors(rc);
                    return rc;
                }
                create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
            }
            rc = check_file(argv);
        }
    }
    else if (rc == ERROR_OPEN_FILE)
    {
        printf("Ошибка открытия файла!\n");
        return ERROR_OPEN_FILE;
    }
    rc = read_to_arr(argv, arr_show_info, &len_arr_show_info);
    if (rc != OK)
    {
        work_with_errors(rc);
        return rc;
    }
    create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);

    choose_menu(&menu);

    while (menu != EXIT)
    {
        switch (menu)
        {
        case ADD_ELEMS:
            saver_len_arr = len_arr_show_info;
            rc = add_to_file(argv, &len_arr_show_info);
            if (rc == ERROR_OPEN_FILE)
            {
                printf("Ошибка открытия файла!\n");
                return ERROR_OPEN_FILE;
            }
            if (rc == ERROR_MAXI_ELEMS)
                printf("Добавлять данные в файл больше нельзя!\n");

            if (saver_len_arr != len_arr_show_info)
            {
                rc = read_to_arr(argv, arr_show_info, &len_arr_show_info);
                if (rc != OK)
                {
                    work_with_errors(rc);
                    return rc;
                }
                create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
            }
            break;

        case REMOVE_ELEM:
            saver_len_arr = len_arr_show_info;
            rc = remove_element(arr_show_info, arr_key_index, &len_arr_show_info);
            switch (rc)
            {
            case ERROR_REMOVE_ELEM:
                printf("Ошибка ввода количества удалений!\n");
                break;
            case ERROR_IN_NAME_SHOW:
                printf("Ошибка введенного названия!\n");
                break;
            }
            if (rc != OK)
                break;
            if (saver_len_arr > len_arr_show_info)
            {
                printf("Удалено %zu элементов!\n", saver_len_arr - len_arr_show_info);
                setting_arr_key(arr_key_index, len_arr_show_info);
                rc = input_data_from_array(argv, arr_show_info, len_arr_show_info);
                if (rc == ERROR_OPEN_FILE)
                {
                    printf("Ошибка открытия файла!\n");
                    return ERROR_OPEN_FILE;
                }
            }
            else
                printf("Не удалено ни одного элемента!\n");
            break;
        case EXIT:
            printf("Программа завершена!\n");
            return OK;

        case PRINT_FIND_ELEMS:
            rc = find_elem(arr_show_info, len_arr_show_info);
            if (rc == ZERO_ELEMS)
                printf("Найдено 0 элементов!\n");
            else if (rc == ERROR_IN_AGE_START)
                printf("Ошибка при введении возраста!\n");
            else if (rc == ERROR_IN_DURATION)
                printf("Ошибка при введении продолжительности!\n");
            break;

        case PRINT_ALL:
            print_all_elems_with_keys(arr_show_info, arr_key_index, len_arr_show_info);
            break;

        case READ_TO_ARR:
            rc = read_to_arr(argv, arr_show_info, &len_arr_show_info);
            if (rc != OK)
            {
                work_with_errors(rc);
                return rc;
            }
            create_arr_keys(arr_show_info, arr_key_index, len_arr_show_info);
            break;

        case SORT_ARR:
            sort_arr_show_info(arr_show_info, len_arr_show_info);
            print_all(arr_show_info, len_arr_show_info);
            break;

        case SORT_ARR_KEY:
            sort_arr_key_index(arr_key_index, len_arr_show_info);
            printf("\nИсходная таблица\n");
            print_all(arr_show_info, len_arr_show_info);
            printf("\n");
            printf("\nОтсортированная таблица при помощи ключей\n");
            print_all_elems_with_keys(arr_show_info, arr_key_index, len_arr_show_info);
            break;

        case ANALISYS:
            rc = analysys_all_sizes(argv, arr_key_index, arr_show_info, len_arr_show_info);
            if (rc == ERROR_ANALIS)
                printf("Нельзя запускать замеры, если элементов менее 1000!\n");
            break;
        }
        choose_menu(&menu);
    }
    return OK;
}
