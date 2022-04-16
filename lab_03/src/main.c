#include "structs_matrix.h"
#include "errors.h"

#include "allocate.h"
#include "read.h"

#include "fill_matrix.h"
#include "sp_matrix_create.h"

#include "multiplication.h"
#include "print.h"

#include "measure_time.h"

int main()
{
    setbuf(stdout, NULL);
    int rc = EXIT_SUCCESS;

    matrix_t matrix, vector_column, result;
    default_matrix_t(&matrix);
    default_matrix_t(&vector_column);
    default_matrix_t(&result);

    special_matrix_t sp_matrix;
    special_vector_column_t sp_vector_column, sp_result;
    default_special_matrix_t(&sp_matrix);
    default_special_vector_t(&sp_vector_column);
    default_special_vector_t(&sp_result);

    int step = -1, rc_step = 0, rc_matrix_t = 0;
    int flag_m = 0, flag_v = 0, flag_r = 0;
    print_main_menu();
    while (step != 0)
    {
        printf("\nВведите пункт меню: ");
        rc_step = input_step_menu(&step, 0, 5);
        if (rc_step == EXIT_SUCCESS)
        {
            if (step == 0)
            {
                if (flag_m)
                {
                    free_matrix(matrix.matrix, matrix.n);
                    default_matrix_t(&matrix);
                    free_special_matrix(&sp_matrix);
                    default_special_matrix_t(&sp_matrix);
                }
                if (flag_v)
                {
                    free_matrix(vector_column.matrix, vector_column.n);
                    default_matrix_t(&vector_column);
                    free_special_vector(&sp_vector_column);
                    default_special_vector_t(&sp_vector_column);
                }
                if (flag_r)
                {
                    free_matrix(result.matrix, result.n);
                    default_matrix_t(&result);
                    free_special_vector(&sp_result);
                    default_special_vector_t(&sp_result);
                }
                printf("До свидания!");
            }
            else if (step == 1)
            {
                int step_one = 0;
                if (matrix.n > 0 && matrix.m > 0)
                {
                    printf("\n Матрица заполнена.");
                    while (step_one != 2 && step_one != 1)
                    {
                        printf("\nПерезаписать матрицу y/n (1/2): ");
                        rc_step = input_step_menu(&step_one, 1, 2);
                        if (rc_step != EXIT_SUCCESS)
                            print_err_matrix(rc_step);
                        if (step_one == 1)
                        {
                            free_matrix(matrix.matrix, matrix.n);
                            free_special_matrix(&sp_matrix);
                            default_matrix_t(&matrix);
                            default_special_matrix_t(&sp_matrix);
                        }
                    }
                }
                if (matrix.n == 0 && matrix.m == 0)
                {
                    step = 0;
                    print_matrix_menu();
                    while (!(step > 0 && step < 4)) {
                        printf("\nВведите пункт: ");
                        rc_step = input_step_menu(&step, 1, 3);
                        if (step == 1)
                            rc_matrix_t = read_usual_matrix_t(&matrix);
                        else if (step == 2)
                            rc_matrix_t = read_special_matrix_t(&matrix);
                        else if (step == 3)
                            auto_fill_matrix(&matrix);
                        else
                            print_err_matrix(rc_step);

                    }
                    if (rc_matrix_t == EXIT_SUCCESS)
                    {
                        (void) create_special_matrix(&sp_matrix, &matrix);
                        printf("\nМатрица успешна введена.");
                        printf("\nОбычная матрица:\n");
                        print_usual_matrix(&matrix);
                        printf("Разряженная матрица:");
                        print_special_matrix(&sp_matrix);
                        flag_m = 1;
                    }
                }
                print_main_menu();
            }
            else if (step == 2)
            {
                int step_one = 0;
                if (vector_column.n > 0 && vector_column.m > 0)
                {
                    printf("\n Вектор-столбец заполнена.");
                    while (step_one != 2 && step_one != 1)
                    {
                        printf("\nПерезаписать вектор-столбец y/n (1/2): ");
                        rc_step = input_step_menu(&step_one, 1, 2);
                        if (rc_step != EXIT_SUCCESS)
                            print_err_matrix(rc_step);
                        if (step_one == 1)
                        {
                            free_matrix(vector_column.matrix, vector_column.n);
                            free_special_vector(&sp_vector_column);
                            default_matrix_t(&vector_column);
                            default_special_vector_t(&sp_vector_column);
                        }
                    }
                }
                if (vector_column.n == 0 && vector_column.m == 0)
                {
                    step = 0;
                    print_vector_menu();
                    while (!(step > 0 && step < 4)) {
                        printf("\nВведите пункт подменю: ");
                        rc_step = input_step_menu(&step, 1, 3);
                        if (step == 1)
                            rc_matrix_t = read_usual_vector_column(&vector_column);
                        else if (step == 2)
                            rc_matrix_t = read_special_vector_column(&vector_column);
                        else if (step == 3)
                            auto_fill_vector_column(&vector_column);
                        else
                            print_err_matrix(rc_step);

                    }
                    if (rc_matrix_t == EXIT_SUCCESS)
                    {
                        (void) create_special_vector(&sp_vector_column, &vector_column);
                        printf("\nВектор-столбец успешно введен.");
                        printf("\nОбычный вектор столбец:\n");
                        print_usual_matrix(&vector_column);
                        printf("Разряженный вектор-стобец:");
                        print_special_vector(&sp_vector_column);
                        flag_v = 1;
                    }
                }
                print_main_menu();
            }
            else if (step == 3)
            {
                if (vector_column.n == 0 || vector_column.m == 0)
                    printf("\n Вектор-столбец не введен!");
                if (matrix.n == 0 || matrix.m == 0)
                    printf("\n Матрица не введена");
                if (vector_column.n > 0 && vector_column.m > 0 &&
                    matrix.n > 0 && matrix.m > 0)
                {
                    int rc_multi = multiply_matrix(&result, &matrix, &vector_column);
                    if (rc_multi == 0)
                    {
                        (void) multiply_special_matrix(&sp_result, &sp_matrix, &sp_vector_column);
                        printf("\nРезультат умножение обычных матриц:\n");
                        print_usual_matrix(&result);
                        printf("Результат умножение разряженных матриц:");
                        print_special_vector(&sp_result);
                        flag_r = 1;
                        print_main_menu();
                    } else
                        printf("\nПри таких размерах матрицу на вектор нельзя умножить:\n  1) %d x %d - размер матрицы n x m\n  2) %d x %d - размер вектора p x r\n  3) %d == %d - m == p",
                                matrix.n, matrix.m,
                                vector_column.n, vector_column.m,
                                matrix.m, vector_column.n);
                }
            }
            else if (step == 4)
            {
                if (vector_column.n == 0 || vector_column.m == 0)
                    printf("\n Вектор-столбец не введен!");
                if (matrix.n == 0 || matrix.m == 0)
                    printf("\n Матрица не введена!");
                if (result.n == 0 || result.m == 0)
                    printf("\n Операции умножения не было произведено!");
                if (matrix.n > 0 && matrix.m > 0)
                {
                    printf("\nМатрица:\n");
                    print_usual_matrix(&matrix);
                    printf("В разреженном ввиде:");
                    print_special_matrix(&sp_matrix);
                }
                if (vector_column.n > 0 && vector_column.m > 0)
                {
                    printf("\nВектор-столбец:\n");
                    print_usual_matrix(&vector_column);
                    printf("В разреженном ввиде:");
                    print_special_vector(&sp_vector_column);
                }
                if (result.n > 0 && result.m > 0)
                {
                    printf("\nРезультат последнего умножения:\n");
                    print_usual_matrix(&result);
                    printf("В разреженном ввиде:");
                    print_special_vector(&sp_result);
                }
                print_main_menu();
            }
            else if (step == 5)
            {
                auto_measure_effinciency();
            }
        } else
        {
            print_err_matrix(rc);
        }
    }
    return rc;
}