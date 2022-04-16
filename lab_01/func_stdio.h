/**
* \file my_func.h
* \brief Модуль с функциями
*/
#ifndef _FUNC_STDIO_H_
#define _FUNC_STDIO_H_
/// Стандартные библиотеки
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/// Постоянные значения
#define M_N                  30
#define ARRAY_SIZE           M_N * 2
#define STRING_FLOAT         100
#define ORDER_UP_OVERFLOW    99999
#define ORDER_DOWN_OVERFLOW -99999
/// Коды ошибки
#define INCORRECT_FLOAT    1
#define MANTISSA_OVERFLOW  2
#define ORDER_OVERFLOW     3
#define M_POINT_ERR        4
#define M_SIGN_ERR         5
#define O_POINT_ERR        6
#define O_SIGN_ERR         7
#define EPS_ERR            8
#define ORDER_INCORRECT    9
#define STRING_OVERFLOW    10
#define STRING_EMPTY       11
/// Структура числа big_float
typedef struct
{
    char sign;
    short mantissa[ARRAY_SIZE];
    size_t size;
    int order;
} big_float;
/**
 * \fn void big_float_default(big_float *num)
 * \brief Функция заполняет значение стурктуры big_float по умолчанию
 *
 * \param [in, out] num укачатель на big_float число
 */
void big_float_default(big_float *num);
/**
 * \fn int read_big_float(big_float *number)
 * \brief Функция считывания данных(специальных вещественных чисел)
 *
 * \param [in, out] number укачатель на big_float число
 * \return Возвращает код ошибки 0 или не нулевой
 */
int read_big_float(big_float *number);

void round_mantissa(big_float *num);
/**
 * \fn void del_zero(big_float *num)
 * \brief Функция убирает лишние нули после умножения чисел
 *
 * \param [in, out] num укачатель на big_float число
 */
void del_zero(big_float *num);
/**
 * \fn void del_zero(big_float *num)
 * \brief Функция свигает на один элемент весь массив вправо
 *
 * \param [in, out] arr укачатель на мантиссу числа big_float
 * \param [in] n размер массива
 */
void swap_right_array(short *arr, size_t n);
/**
 * \fn void multiple_arr_to_int(big_float *res, const big_float *num, short fg, short digit)
 * \brief Функция умножает первое число на цифру из второго числа исходя из разрядности цифры
 *
 * \param [in, out] res укачатель на результат умнложения числа типа big_float
 * \param [in] num константный указатель на число, на котрое умножают
 * \param [in] fg цифра из второго числа, которая передано, чтобы умножить число num
 * \param [in] digit разрядность цифры второго числа
 */
void multiple_arr_to_int(big_float *res, const big_float *num, short fg, short digit);
/**
 * \fn big_float sum_big_float(const big_float *num1, const big_float *num2)
 * \brief Функция суммирует два числа структуры big_float
 *
 * \param [in] num1 константный указатель на первое число суммы
 * \param [in] num1 константный указатель на второе число суммы
 * \return Возращает число big_float - результат суммы
 */
big_float sum_big_float(const big_float *num1, const big_float *num2);
/**
 * \fn big_float multiple_big_float(big_float num1, big_float num2)
 * \brief Функция умножает два числа структуры big_float
 *
 * \param [in] num1 константный указатель на первое число суммы
 * \param [in] num1 константный указатель на второе число суммы
 * \return Возращает число big_float - результат умножения
 */
big_float multiple_big_float(big_float num1, big_float num2);

/**
 * \fn void print_b();
 * \brief Функция формуриет текст перед вводом
 */
void print_b();
/**
 * \fn void print_task()
 * \brief Функция формуриет текст задания
 */
void print_task();
/**
 * \fn void print_error(short rc)
 * \brief Функция выводит сообщение об ошибке
 *
 * \param [in] rc код ошибки
 */
void print_error(short rc);
/**
 * \fn void print_big_float(big_float *number)
 * \brief Функция вывода числа структуры big_float
 *
 * \param [in] number указатель на число big_float
 */
void print_big_float(big_float *number);

#endif