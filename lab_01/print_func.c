/**
 * \file print_func.c
 * \brief Файл с функциями для формирование вывода
 */
#include "func_stdio.h"

void print_b()
{
    printf("Введите вещественное число:");
    for (size_t i = 0; i < M_N; i++)
       printf(" ");
    printf("|");
    for (size_t i = 0; i < M_N + 1; i++)
       printf("\b");
}

void print_task()
{
    printf("------------------------Умножение двух вещественных чисел---------------------\n");
    printf("Формат ввода может вводит как целое, так и вещественное и экспонированном виде\n +-M.Ne+-K\n");
    printf("Вывод в виде +-0.N+Me+-K\n");
    printf("Пределы ввода, сумма N, M не превышает 30 значимых цифр, а порядок K - 5 цифр!\n");
    printf("------------------------------------------------------------------------------\n");
}

void print_error(short rc)
{
    switch(rc)
    {
        case INCORRECT_FLOAT:
            printf("Warning! Некорректно записано вещественное число!\n");
            break;
        case MANTISSA_OVERFLOW:
            printf("Warning! В мантиссе больше 30 элементов!\n");
            break;
        case ORDER_OVERFLOW:
            printf("Warning! В порядке больше 5 цифр!\n");
            break;
        case M_POINT_ERR:
            printf("Warning! В вещественном числе находятся несколько точек, в мантиссе!\n");
            break;
        case M_SIGN_ERR:
            printf("Warning! Записано несколько знаков перед мантиссой или в самой мантиссе!\n");
            break;
        case O_POINT_ERR:
            printf("Warning! В порядке не должно быть точек!\n");
            break;
        case O_SIGN_ERR:
            printf("Warning! Записано несколько знаков перед порядком или в самом порядке!\n");
            break;
        case EPS_ERR:
            printf("Warning! В числе находятся несколько обозначений \"e\" либо только \"e\"!\n");
            break;
        case ORDER_INCORRECT:
            printf("Warning! В порядке ошибка!\n");
            break;
        case STRING_OVERFLOW:
            printf("Warning! Переполнение возможно допустимых введенных значений!\n");
            break;
        case STRING_EMPTY:
            printf("Warning! Введена пустая строка!\n");
            break;
        default:
            break;
    }
}

void print_big_float(big_float *number)
{
    if (number->sign == '-')
        printf("%c", number->sign);
    printf("0.");
    if (number->size == 0)
        printf("0");
    else
        for (size_t i = 0; i < number->size; i++)
            printf("%hd", number->mantissa[i]);
    printf("e%d\n", number->order);
}