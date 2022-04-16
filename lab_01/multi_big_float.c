/**
 * \file multi_big_float.c
 * \brief Файл с функциями для умножение чисел big_float
 */
#include "func_stdio.h"

void round_mantissa(big_float *num)
{
    short mod = 0, decade = 0, sum= 0;
    if (num->mantissa[M_N] >= 5)
    {
        decade = 1;
        for (int i = num->size - 1; i >= 0 && decade > 0; i--)
        {
            sum = num->mantissa[i] + decade;
            decade = sum / 10;
            mod = sum % 10;
            num->mantissa[i] = mod;
        }
        if (decade > 0)
        {
            swap_right_array(num->mantissa, num->size);
            num->mantissa[0] = decade;
            decade = 0;
        }
    }
}

void del_zero(big_float *num)
{
    for (int i = num->size - 1; i >= 0 && num->mantissa[i] == 0; i--)
        num->size = num->size - 1;
}

void swap_right_array(short *arr, size_t n)
{
    for (int i = n - 1; i >= 0; i--)
        arr[i] = arr[i - 1];
    arr[0] = 0;
}

void multiple_arr_to_int(big_float *res, const big_float *num, short fg, short digit)
{
    res->size = num->size + digit;
    short multi = 0, mod = 0, decade = 0;
    int i = num->size - 1;
    for (; i >= 0; i--)
    {
        multi = num->mantissa[i] * fg + decade;
        mod = multi % 10;
        decade = multi / 10;
        res->mantissa[i] = mod;
    }
    if (num->size < ARRAY_SIZE && decade > 0)
    {
        swap_right_array(res->mantissa, ++res->size);
        res->mantissa[++i] = decade;
    }
}

big_float sum_big_float(const big_float *num1, const big_float *num2)
{
    big_float result;
    big_float_default(&result);
    result.size = num1->size > num2->size ? num1->size : num2->size;
    short sum = 0, mod = 0, decade = 0;
    int i = result.size - 1;
    for (int inum1 = num1->size - 1, inum2 = num2->size - 1; i >= 0; i--)
    {
        if (inum1 < 0)
        {
            sum = num2->mantissa[inum2] + decade;
            inum2--;
        } else if (inum2 < 0)
        {
            sum = num1->mantissa[inum1] + decade;
            inum1--;
        } else
        {
            sum = num1->mantissa[inum1] + num2->mantissa[inum2] + decade;
            inum1--;
            inum2--;
        }
        mod = sum % 10;
        decade = sum / 10;
        result.mantissa[i] = mod;
    }
    if (result.size < ARRAY_SIZE && decade > 0)
    {
        swap_right_array(result.mantissa, ++result.size);
        result.mantissa[++i] = decade;
    }
    return result;
}

big_float multiple_big_float(big_float num1, big_float num2)
{
    big_float result, buff;
    big_float_default(&result);
    big_float_default(&buff);
    result.size = num1.size > num2.size ? num1.size : num2.size;
    short i = num2.size - 1, j = 0;
    for(;i >= 0; i--, j++)
    {
        buff.size = result.size;
        multiple_arr_to_int(&buff, &num1, num2.mantissa[i], j);
        result = sum_big_float(&result, &buff);
        big_float_default(&buff);
    }
    if (result.size > M_N)
        result.size = M_N;
    if (num1.size == 1 || num2.size == 1)
        result.order--;
    result.order += num1.order + num2.order;
    if ((num1.sign == '-' && num2.sign == '+') || (num1.sign == '+' && num2.sign  == '-'))
        result.sign = '-';
    round_mantissa(&result);
    del_zero(&result);
    return result;
}