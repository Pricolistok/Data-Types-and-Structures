#include <stdio.h>
#include "struct.h"
#include "errors.h"
#include "const.h"
#include "process.h"

// Функция для выравнивания целого числа перед делением
// Функция принимает массив целых чисел для записи обработанного числа, массив целых чисел, откуда берутся данные, длинну целой части вещественного числа,
// длинну дробной части вещественного числа, длинну целого числа, а так же адрес на переменную для хранения "указателя" на цифру внутри числа
void stabilize_nums(int buffer[LEN_MANTISSA * 2], int integer_arr[], size_t len_num_float, size_t len_integer_arr, size_t *cursor)
{
    size_t cursor_add = 0;

    while (cursor_add < len_integer_arr + len_num_float)
    {
        // printf("CUR %zu\n", cursor_add);
        if (cursor_add < len_integer_arr)
            buffer[cursor_add] = integer_arr[cursor_add];
        else
            buffer[cursor_add] = 0;
        cursor_add++;
    }
    printf("curadd %zu\n", cursor_add);
    *cursor = cursor_add;
}

// Функция для объединения вещественного числа в один массив
// Функция принимает массив, в который будет записн обработанный массив, адрес на структура, длинна целой части, длинна дробной части
void write_to_all_num(int all_float_num[], valid_numbers *number, size_t len_num_int, size_t len_num_float, size_t *cursor_save)
{
    size_t cursor = 0;
    int flag = 0;
    for (size_t i = 0; i < len_num_int; i++)
    {
        if  ((flag == 0) && (number->mantissa_integer[i] != 0))
            flag = 1;
        if (flag != 0)
        {
            all_float_num[cursor] = number->mantissa_integer[i];
            cursor++;
        }
    }
    for (size_t i = 0; i < len_num_float; i++)
    {
        all_float_num[cursor] = number->mantissa_float[i];
        cursor++;
    }
    *cursor_save = cursor;
}

// Функция для вычетания делителя из делимого
// Функиця принимает массив челых чисел из которого происходит вычетание, массив целых чисел, которых хранит в себе вычетаемое число
// массив целых чисел, который хранит в себе результат вычетания, длинну чисал из которого вычетают,
// адрес на переменную храняющую длинну массива с результатом, перменная хранящаю разницу между длинами чисел,
// адрес на переенную хранящую результат деления, адрес на переменную хранящую длинну итогового массива
void substracting(int num[LEN_MANTISSA], int all_float_num[LEN_MANTISSA], int history_arr[LEN_MANTISSA], size_t len_num, size_t *len_hist, size_t checker, int *need_sub)
{
    int flag = 0, cnt = 0;
    int arr_shift[LEN_MANTISSA * 2 + 1];
    int arr_result_buf[LEN_MANTISSA];
    size_t cursor = 0, len_buffer = len_num;
    int buffer[LEN_MANTISSA * 2 + 1];
    for (size_t i = 0; i < len_buffer; i++)
        buffer[i] = num[i];
    for (size_t i = 0; i < len_buffer; i++)
    {
        if (i < checker)
            arr_shift[i] = 0;
        else
            arr_shift[i] = all_float_num[i - checker];
    }
    // printf("shify^ ");
    // for (size_t i = 0; i < len_buffer; i++)
    //     printf("%d", arr_shift[i]);
    // printf("\n");

    while (flag != 1)
    {
        // printf("len %zu\n", len_buffer);
        // printf("BUFF^ ");
        // for (size_t i = 0; i < len_buffer; i++)
        //     printf("%d", buffer[i]);
        // printf("\n");
        // printf("SHIFT^ ");
        // for (size_t i = 0; i < len_buffer; i++)
        //     printf("%d", arr_shift[i]);
        // printf("\n");
        for (int i = len_buffer - 1; i >= 0; i--)
        {
            // printf("i^ %i buf[i]^ %d shift[i]^ %d res^ %d\n", i, buffer[i], arr_shift[i], buffer[i] - arr_shift[i]);
            if (buffer[i] - arr_shift[i] >= 0)
            {
                arr_result_buf[cursor] = buffer[i] - arr_shift[i];
                cursor++;
            }
            else if (i != 0)
            {
                for (int j = i - 1; j >= 0; j--)
                {

                    if (buffer[j] > 0)
                    {
                        arr_result_buf[cursor] = (10 + buffer[i]) - arr_shift[i];
                        cursor++;
                        buffer[j] = buffer[j] - 1;
                        break;
                    }
                    else if (j == 0 && buffer[j] - 1 <= 0)
                    {
                        flag = 1;
                        break;
                    }
                    else
                    {
                        if (buffer[j] == 0)
                            buffer[j] = 9;
                        else
                            buffer[j] = buffer[j] - 1;
                    }
                }
                if (flag == 1)
                {
                    break;
                }
            }
            else
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            break;
        }

        if (flag == 2)
        {
            for (size_t k = 0; k < *len_hist; k++)
                history_arr[k] = 0;
        }
        // *res_len = cursor;
        *len_hist = len_buffer;

        for (size_t k = 0; k < len_buffer; k++)
        {
            if (k < len_buffer - cursor)
            {
                buffer[k] = 0;
                history_arr[k] = 0;
            }
            else
            {
                buffer[k] = arr_result_buf[cursor - 1];
                history_arr[k] = arr_result_buf[cursor - 1];
                cursor--;
            }
        }
        cursor = 0;
        cnt++;
    }
    *need_sub = cnt;
}

void print_arr(int arr[], size_t len)
{
    printf("ARRAY: \n");
    for (size_t i = 0; i < len; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int cnt_summ(int arr[], size_t len)
{
    int cnt = 0;
    for (size_t i = 0; i < len; i++)
        cnt += arr[i];
    return cnt;
}

// Основная функция деления, которая последовательно вызвает остальные функции в этом файле, а так же возвращает результат
// Функция принимает адрес на структуру, массив целых чисел, хранящий результат, адрес на длинну итогового массива,
// массив целых чисел, хранящий целое число, длинну целой части дробного числа, длинну  дробной части дробного числа,
// длинну целого числа, адрес на переменную, хранящую место постановки точки
int separator(valid_numbers *number, int arr_result[LEN_MANTISSA + 1], size_t *len_res_arr, int integer_arr[], size_t len_num_int, size_t len_num_float, size_t len_integer_arr, int *cnt_z)
{
    int new_num[LEN_MANTISSA * 2], num_now[LEN_MANTISSA];
    int all_mantissa[LEN_MANTISSA], history_arr[LEN_MANTISSA];
    int need_sub = 0, checker_len = 0, cnt_sum_hist = 0, flag_stop = 0, flag_del_zeros = 0, flag_dot = -1, cnt_after = 0;
    size_t cursor_new_num = 0, cnt_add_zeros = 0;
    size_t len_new_num = 0, len_res = 0, len_history = 0, len_num_now = 0, len_mantissa = 0;
    stabilize_nums(new_num, integer_arr, len_num_float, len_integer_arr, &len_new_num);
    write_to_all_num(all_mantissa, number, len_num_int, len_num_float, &len_mantissa);
    if (cnt_summ(all_mantissa, len_mantissa) == 0)
        return ERROR_SUB_ZERO;
    if (cnt_summ(new_num, len_new_num) == 0)
        return ZERO_NUM;
    // print_arr(new_num, len_new_num);
    // printf("MAN %zu", len_mantissa);
    // print_arr(all_mantissa, len_mantissa);
    if (len_num_int > len_integer_arr)
        flag_dot = -2; 
    while (len_res < LEN_MANTISSA + 1)
    {
        if (len_num_now < len_mantissa)
        {
            if (cursor_new_num < len_new_num)
            {
                cnt_add_zeros++;
                num_now[len_num_now] = new_num[cursor_new_num];
                len_num_now++;
                cursor_new_num++;
                if ((cnt_add_zeros >= 2) && (len_res != 0))
                {
                    arr_result[len_res] = 0;
                    len_res++;
                }
            }
            else
            {
                cnt_add_zeros++;
                if (flag_dot == -1)
                {
                    flag_dot = len_res;
                }
                if ((cnt_add_zeros >= 2) && (len_res != 0))
                {
                    arr_result[len_res] = 0;
                    len_res++;
                }
                num_now[len_num_now] = 0;
                len_num_now++;
                cursor_new_num++;
            }
        }
        else
        {
            checker_len = len_num_now - len_mantissa;
            substracting(num_now, all_mantissa, history_arr, len_num_now, &len_history, checker_len, &need_sub);
            while (need_sub < 1)
            {
                if (cursor_new_num < len_new_num)
                {
                    num_now[len_num_now] = new_num[cursor_new_num];
                    len_num_now++;
                    cursor_new_num++;
                    cnt_add_zeros++;
                    if ((cnt_add_zeros >= 2) && (len_res != 0))
                    {
                        arr_result[len_res] = 0;
                        len_res++;
                    }
                }
                else
                {
                    num_now[len_num_now] = 0;
                    len_num_now++;
                    cnt_add_zeros++;
                    if (flag_dot == -1)
                        flag_dot = len_res;
                    if ((cnt_add_zeros >= 2) && (len_res != 0))
                    {
                        arr_result[len_res] = 0;
                        len_res++;
                    }
                }
                checker_len = len_num_now - len_mantissa;
                substracting(num_now, all_mantissa, history_arr, len_num_now, &len_history, checker_len, &need_sub);
                if ((need_sub == 0) && (len_num_now > len_mantissa + 1))
                {
                    flag_stop = 1;
                    break;
                }
            }
            cnt_add_zeros = 0;
            if (flag_stop == 1)
                break;
            arr_result[len_res] = need_sub;
            len_res++;

            for (size_t i = 0; i < len_new_num; i++)
                num_now[i] = 0;
            len_num_now = 0;
            cnt_sum_hist = 0;
            for (size_t i = 0; i < len_history; i++)
            {
                if ((flag_del_zeros == 0) && (history_arr[i] != 0))
                    flag_del_zeros = 1;
                if (flag_del_zeros == 1)
                {
                    cnt_sum_hist += history_arr[i];
                    num_now[len_num_now] = history_arr[i];
                    history_arr[i] = 0;
                    len_num_now++;
                }
            }
            flag_del_zeros = 0;
            for (size_t i = cursor_new_num; i < len_new_num; i++)
                cnt_after += new_num[i];
            if ((need_sub != 0) && (cnt_sum_hist == 0) && (cnt_after == 0))
            {
                for (size_t i = cursor_new_num; i < len_new_num; i++)
                {
                    arr_result[len_res] = 0;
                    len_res++;
                }
                break;
            }
            // if ((need_sub != 0) && (cnt_sum_hist == 0) && (cursor_new_num < len_new_num))
            // {
            //     printf("PPPPPP\n");
            //     while (len_num_now < len_mantissa)
            //     {
            //         arr_result[len_res] = 0;
            //         len_res++;
            //         num_now[len_num_now] = new_num[cursor_new_num];
            //         len_num_now++;
            //         cursor_new_num++;
            //     }
            // }
            if ((cnt_sum_hist == 0) && (cursor_new_num > len_new_num))
                break;
            // cnt_add_zeros++;
        }
    }
    *len_res_arr = len_res;
    printf("RESULT: ");
    for (size_t i = 0; i < *len_res_arr; i++)
        printf("%d ", arr_result[i]);
    printf("\n");
    printf("%d\n", flag_dot);
    if (flag_dot == -1)
        flag_dot = len_res;
    else if (flag_dot == -2)
        flag_dot = len_integer_arr - len_num_int + 1;
    *cnt_z = flag_dot;
    return OK;
}
