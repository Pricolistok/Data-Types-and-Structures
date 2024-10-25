#include "const.h"
#include "stdio.h"
#include "errors.h"
#include "input_output.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


// Функция ввода порядка числа
// Функция принимает адрес на структуру
int input_order(valid_numbers *number)
{
    int ord_saver, flag = 1;
    char order[LEN_ORDER + 3];
    size_t i = 0;
    printf("Введите порядок: \n");
    printf("---------1---------2---------3---------4---------5\n");
    fgets(order, LEN_ORDER + 3, stdin);
    if (order[strlen(order) - 1] != '\n' || strlen(order) == 1)
    {
        return ERROR_LEN_ORDER;
    }
    order[strlen(order) - 1] = 0;
    if ((order[i] == '+') || (order[i] == '-'))
    {
        i = 1;
    }
    for (; i < strlen(order); i++)
    {
        if (!isdigit(order[i]))
            return ERROR_SYMBOL_IN_ORDER;
    }
    ord_saver = atoi(order) * flag;
    if ((ord_saver < -99999) || (ord_saver > 99999))
        return ERROR_LEN_ORDER;
    number->order = ord_saver;
    return OK;
}

// Функция ввода массивов, которая так же проверяет длинну на 0
// Функция принимает массив симоволов, в который записывает результат ввода, длинну считвания, а также параметр для выбора ввода
int input_symbols(char num[LEN_MANTISSA + 3], size_t len_num, int code)
{
    if (code == 0)
        printf("Введите мантису:\n");
    else
        printf("Введите целое число:\n");
    printf("---------1---------2---------3---------4---------5\n");
    fgets(num, len_num, stdin);
    if (num[strlen(num) - 1] != '\n' || strlen(num) == 1)
    {
        return ERROR_LEN_NUM;
    }
    num[strlen(num) - 1] = 0;
    return OK;
}

// Функция проверки символов внутри массива хранящего значения для мантисы
// Функция принимает массив символов, с которого считываются данные, массив символов, куда считывается целая часть вещественного числа, массив
// куда считывается дробная часть вещественного числа, адрес на переменную, хранящую знак числа
// адрес на переменную, хрнящую длинну дробной части, адрес на перменную, хранящую длинну целой части вещественного числа
int check_elem_float(char saver_full_number[LEN_MANTISSA + 3], char mantissa_saver_integer[LEN_MANTISSA + 2], char mantissa_saver_float[LEN_MANTISSA + 2], int *flag, size_t *len_float, size_t *len_int)
{
    int cursor = 0, cnt_dots = 0;
    for (size_t i = 0; i < strlen(saver_full_number); i++)
    {
        if ((i == 0) && ((saver_full_number[i] == '-')))
            *flag = -1;
        else if ((i == 0) && ((saver_full_number[i] == '+')))
            continue;
        else if (saver_full_number[i] == '.')
        {
            if (cnt_dots == 1)
                return ERROR_DOT_IN_NUM;
            cnt_dots++;
            cursor = 0;
        }
        else if (isdigit(saver_full_number[i]) != 0)
        {
            if (cnt_dots == 0)
            {
                if ((*len_int == 0) && (saver_full_number[i] == '0'))
                    continue;
                else
                {
                    mantissa_saver_integer[cursor] = saver_full_number[i];
                    cursor++;
                    *len_int = *len_int + 1;
                }
            }
            else
            {
                mantissa_saver_float[cursor] = saver_full_number[i];
                cursor++;
                *len_float = *len_float + 1;
            }
        }
        else
        {
            return ERROR_SYMBOL_IN_NUM;
        }
    }
    return OK;
}

// Фнукция записи данных в структуру
// Функция принимает адрес на структуру, длинну целой части, длинну дробной части
int input_float_arr(valid_numbers *number, size_t *len_num_int, size_t *len_num_float)
{
    int rc, flag = 1;
    size_t cnt = 0, len_int = 0, len_float = 0;
    char saver_full_number[LEN_MANTISSA + 3];
    char mantissa_saver_integer[LEN_MANTISSA + 2], mantissa_saver_float[LEN_MANTISSA + 2];

    rc = input_symbols(saver_full_number, LEN_MANTISSA + 3, 0);
    if (rc != OK)
        return rc;
    rc = check_elem_float(saver_full_number, mantissa_saver_integer, mantissa_saver_float, &flag, &len_float, &len_int);
    // printf("%ld %d\n", len_int, rc);
    if (rc != OK)
        return rc;
    if((len_int == 0) && (len_int + len_float) > 39)
        return ERROR_LEN_FULL_NUM;
    else if((len_int != 0) && (len_int + len_float) > 40)
        return ERROR_LEN_FULL_NUM;
    else if (len_int == 0)
    {
        number->mantissa_integer[0] = 0;
        len_int++;
        number->sign = flag;
    }
    else
    {
        for (size_t i = 0; i < len_int; i++)
        {
            number->mantissa_integer[i] = (mantissa_saver_integer[i] - '0');
            cnt++;
        }
        number->sign = flag;
        cnt = 0;
    }
    for (size_t i = 0; i < len_float; i++)
    {
        number->mantissa_float[i] = (mantissa_saver_float[i] - '0');
        cnt++;
    }
    
    *len_num_int = len_int;
    *len_num_float = len_float;

    return OK;
}

// Функция проверки целого в массиве символов
// Функция принимает массив символов, в котором хранится все целое число, массив целых чисел, куда записывается результат обработки,
// Адресс на перменную, хрянящую длинну массива, адрес на переменную хранящую знак числа
int write_elem_integer(char saver_full_number[LEN_MANTISSA], int integer_arr[LEN_MANTISSA], size_t *len_int, int *flag)
{
    int cursor = 0;
    for (size_t i = 0; i < strlen(saver_full_number); i++)
    {
        if ((i == 0) && ((saver_full_number[i] == '-')))
            *flag = -1;
        else if ((i == 0) && ((saver_full_number[i] == '+')))
            continue;
        else if (isdigit(saver_full_number[i]) != 0)
        {
            if ((*len_int == 0) && (saver_full_number[i] == '0'))
                continue;
            else
            {
                integer_arr[cursor] = saver_full_number[i] - '0';
                *len_int = *len_int + 1;
                cursor++;  
            }
            
        }
        else
            return ERROR_SYMBOL_IN_NUM;
    }

    return OK;
}

// Функция записи символов в массив, хранящий целое число
// Функция принимает массив целых чисел, адрес на длину этого массива, а также адрес на переменную для хранения знака
int input_integer_arr(int integer_arr[], size_t *len_num_int, int *sign)
{
    int rc, flag = 1;
    size_t len_int = 0;
    char saver_full_number[LEN_MANTISSA + 3];

    rc = input_symbols(saver_full_number, LEN_MANTISSA + 3, 1);
    if (rc != OK)
        return rc;
    rc = write_elem_integer(saver_full_number, integer_arr, &len_int, &flag);
    if (rc != OK)
        return rc;
    *sign = flag;
    if (len_int > 40)
        return ERROR_LEN_FULL_NUM;
    *len_num_int = len_int;
    return OK;
}

// Функция для округления результата перед выводом
// Функция принимает массив целых чисел, а так же адрес на переменную хранящую длину
void round_arr(int arr_result[LEN_MANTISSA], size_t *len_res_arr)
{
    size_t len = *len_res_arr;
    size_t saver_i = 0;
    for (size_t i = *len_res_arr - 1; i >= 1; i--)
    {
        if (arr_result[i] == 0)
            len--;
        else
            break;
    }
    *len_res_arr = len;
    if (*len_res_arr >= LEN_MANTISSA)
    {
        printf("IIn\n");
        if (arr_result[*len_res_arr - 1] >= 5)
        {
            printf("UUUUU\n");
            arr_result[*len_res_arr - 2] = arr_result[*len_res_arr - 2] + 1;

            for (int i = *len_res_arr - 2; i >= 0; i--)
            {
                if (arr_result[i] == 10)
                {
                    len--;
                    arr_result[i - 1] = arr_result[i - 1] + 1;
                }
                // else if (arr_result[i] >= 5)
                // {
                //     len--;
                //     arr_result[i - 1] = arr_result[i - 1] + 1;
                // }
                else
                {
                    break;
                }
                saver_i = i;
            }
            if (arr_result[saver_i] == 10)
            {
                arr_result[saver_i] = 0;
                len--;
            }

            *len_res_arr = len;
        }
    }
    
    for (size_t i = *len_res_arr - 1; i >= 1; i--)
    {
        if (arr_result[i] == 0)
            len--;
        else
            break;
    }
    *len_res_arr = len;
}


// Функция вывода результата
// Функция принимает адрес на структуру, также массив целых чисел, длинну массива, знак целогого числа, а также переменную для подсчета порядка
int print_result(valid_numbers *number, int arr_result[LEN_MANTISSA], size_t *len_res_arr, int sign_int, int cnt_zero)
{
    char sign_str[LEN_SIGN];
    int n_sign = number->sign;
    int order = number->order, cnt = 0;
    for (size_t i = 0; i < *len_res_arr; i++)
        cnt += arr_result[i];
    if (cnt != 0)
        round_arr(arr_result, len_res_arr);
    else
    {
        arr_result[0] = 0;
        *len_res_arr = 1;
    }
    cnt = 0;
    for (size_t i = 0; i < *len_res_arr; i++)
    {
        if (arr_result[i] == 0)
            *len_res_arr = *len_res_arr - 1;
        else
            break;
    }
    if (*len_res_arr > LEN_MANTISSA)
        *len_res_arr = LEN_MANTISSA;
    if ((cnt_zero - order > 99999) || (cnt_zero - order < -99999))
        return ERROR_ORDER;
    if (n_sign * sign_int < 0)
        sign_str[0] = '-';
    else
        sign_str[0] = '+';
    for (size_t i = 0; i < *len_res_arr; i++)
        cnt += arr_result[i];
    if (cnt == 0)
    {
        *len_res_arr = 1;
        arr_result[0] = 0;
    }
    printf("zeor %d\n", order);
    printf(">+---------1---------2---------3---------4---------5\n");
    printf("%c0.", sign_str[0]);
    for (size_t i = 0; i < *len_res_arr; i++)
    {
        printf("%d", arr_result[i]);
    }
    printf(" E%d\n", cnt_zero - order);
    return OK;
}
