/**
 * \file read_big_float.c
 * \brief Файл с функцией для чтения чисел big_float и установление значений по умолчанию
 */
#include "func_stdio.h"

void big_float_default(big_float *num)
{
    num->size = 0;
    num->order = 0;
    num->sign = '+';
    for (size_t i = 0; i < ARRAY_SIZE; i++)
        num->mantissa[i] = 0;
}

int read_big_float(big_float *number)
{
    char str[STRING_FLOAT] = { 0 };
    int rc = EXIT_SUCCESS;
    short n = 0, m = 0;
    int order = 0, order_p = 0;
    _Bool point = 0, sign = 0, eps = 0, flag = 0;
    size_t i = 0;
    if (fgets(str, STRING_FLOAT + 2, stdin) == NULL)
        return STRING_EMPTY;
    if (str[strlen(str) - 1] == '\n')
        str[strlen(str) - 1] = '\0';
    if (strlen(str) > STRING_FLOAT)
        return STRING_OVERFLOW;
    if (strlen(str) == 0)
        return STRING_EMPTY;
    if (str[i] == 'e' || str[i] == 'E')
        return EPS_ERR;
    if (str[i] == '-' || str[i] == '+')
    {
        number->sign = str[i];
        i++;
    } else
        number->sign = '+';
    while (i < (M_N + point + sign + 1) && str[i] != '\0' && eps == 0)
    {
        if ((str[i] == '.' || str[i] == ',') && !point)
            point = 1;
        else if (str[i] == 'e' || str[i] == 'E')
        {
            eps = 1;
        }
        else if ('0'<= str[i] && str[i] <= '9')
        {

            if (str[i] == '0' && !flag)
            {
                if (point)
                    order_p--;
                i++;
                continue;
            }
            if (str[i] != '0')
            {
                if (!flag)
                    flag = 1;
            }
            number->mantissa[m + n] = (short) (str[i] - '0');
            if (point)
                n++;
            else
                m++;
        }
        else
        {
            if (str[i] == '-' || str[i] == '+')
                return M_SIGN_ERR;
            if (str[i] == '.' || str[i] == ',')
                return M_POINT_ERR;
            else
                return INCORRECT_FLOAT;
        }
        i++;
    }
    if (i - point - eps - sign > M_N)
        return MANTISSA_OVERFLOW;
    number->size = (m + n);
    if (eps || rc == 0)
    {
        if (str[i] == '-' || str[i] == '+')
        {
            if (str[i] == '-')
                sign = 1;
            i++;
        }
        for (; str[i] != '\0'; i++)
        {
            if ('0'<= str[i] && str[i] <= '9')
                order = order * 10 + (int) (str[i] - '0');
            else
            {
                if (str[i] == '-' || str[i] == '+')
                    return O_SIGN_ERR;
                else if (str[i] == '.' || str[i] == ',')
                    return O_POINT_ERR;
                else if (str[i] == 'e' || str[i] == 'E')
                    return EPS_ERR;
                else
                    return ORDER_INCORRECT;
            }
        }
        if (sign)
        {
            sign = 0;
            order *= -1;
        }
    }
    if (number->size != 0)
        number->order = m + order + order_p;
    if (number->size == 0)
    {
        n = 1;
        number->size = 1;
    }
    //if (number->order > ORDER_UP_OVERFLOW || number->order < ORDER_DOWN_OVERFLOW)
    //    return ORDER_OVERFLOW;
    return rc;
}
