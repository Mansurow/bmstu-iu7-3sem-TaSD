/**
 * \file main.c
 * \brief Файл с функциями main
 */
#include "func_stdio.h"

int main()
{
    setbuf(stdout, NULL);
    int rc = EXIT_SUCCESS;
    big_float num_float_1, num_float_2, res_float;
    big_float_default(&num_float_1);
    big_float_default(&num_float_2);
    big_float_default(&res_float);
    print_task();
    print_b();
    rc = read_big_float(&num_float_1);
    printf("\n");
    if (rc == EXIT_SUCCESS)
    {
        print_b();
        rc = read_big_float(&num_float_2);
        printf("\n");
        if (rc == EXIT_SUCCESS)
        {
            res_float = multiple_big_float(num_float_1, num_float_2);
            if (res_float.order > ORDER_UP_OVERFLOW ||  res_float.order < ORDER_DOWN_OVERFLOW)
                rc = ORDER_OVERFLOW;
            else
            {
                printf("Результат: ");
                print_big_float(&res_float);
            }
        }
    }
    print_error(rc);
    return rc;
}