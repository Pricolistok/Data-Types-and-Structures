#include <stdio.h>
#include "errors.h"
#include "const.h"
#include "input_output.h"
#include "process.h"
#include "struct.h"
#include "process.h"

// Главная функция программы
int main()
{
	// Объявление перменных
	valid_numbers number;
	int rc, cnt_z = 0;
	size_t len_num_int, len_num_float, len_integer_arr;
	int integer_arr[LEN_MANTISSA], sign_int;
	int arr_result[LEN_MANTISSA + 1];
	size_t len_res_arr = 0;

	printf("Программа для деления целого числа на вещественное\n");
	// Вызов функции ввода целого числа
	printf("Длинна целого числа не превышает 40 символов, также возможен ввод незначимых нулей\n");
	rc = input_integer_arr(integer_arr, &len_integer_arr, &sign_int);
	// Обработка ошибок при вводе
	if (rc == ERROR_SYMBOL_IN_NUM)
	{
		printf("Ошибка символа в числе\n");
		return ERROR_SYMBOL_IN_NUM;
	}
	else if (rc == ERROR_LEN_NUM)
	{
		printf("Ошибка длинны числа\n");
		return ERROR_LEN_NUM;
	}
	else if(rc == ERROR_LEN_FULL_NUM)
	{
		printf("Ошибка длинны числа\n");
		return ERROR_LEN_FULL_NUM;
	}
	// Вызов функции ввода вещественного числа
	printf("Длинна вещественного числа не превышает 40 символов и представляется в виде ±m.n Е±K\n");
	rc = input_float_arr(&number, &len_num_int, &len_num_float);
	// Оработка ошибок при вводе
	if (rc == ERROR_LEN_NUM)
	{
		printf("Ошибка длинны мантисы\n");
		return ERROR_LEN_NUM;
	}
	else if (rc == ERROR_DOT_IN_NUM)
	{
		printf("Введено более одной точки\n");
		return ERROR_DOT_IN_NUM;
	}
	else if (rc == ERROR_SYMBOL_IN_NUM)
	{
		printf("Ошибка символа в числе\n");
		return ERROR_SYMBOL_IN_NUM;
	}
	else if(rc == ERROR_LEN_FULL_NUM)
	{
		printf("Ошибка длинны числа\n");
		return ERROR_LEN_FULL_NUM;
	}
	// Вызов функции для ввода порядка вещественного числа
	printf("Порядок представляет собой целое число от -99999 до +99999\n");
	rc = input_order(&number);
	// Обработка ошибок ввода
	if (rc == ERROR_SYMBOL_IN_ORDER)
	{
		printf("Ошибка символа при введении порядка числа\n");
		return ERROR_SYMBOL_IN_ORDER;
	}
	else if (rc == ERROR_LEN_ORDER)
	{
		printf("Ошибка длинны порядка\n");
		return ERROR_LEN_ORDER;
	}

	// Вызов функции деления числа
	rc = separator(&number, arr_result, &len_res_arr, integer_arr, len_num_int, len_num_float, len_integer_arr, &cnt_z);
	// Обработка ошибок при делениии
	if (rc == ERROR_SUB_ZERO)
	{
		printf("Ошибка деления на ноль\n");
		return ERROR_SUB_ZERO;
	}
	// Обработка случая деления 0 на число
	if (rc == ZERO_NUM)
	{
		sign_int = 1;
		number.sign = 1;
		number.order = 0;
	}

	// Вызов функции вывода
	printf("Вывод представляется в формате ±0.m1 Е±K1, где m1 - до 40 значащих цифр, а K1 - порядок\n");
	rc = print_result(&number, arr_result, &len_res_arr, sign_int, cnt_z);
	// Обработка ошибок при выводе
	if (rc == ERROR_ORDER)
	{
		printf("Ошибка порядка\n");
		return ERROR_ORDER;
	}

	return rc;
}
