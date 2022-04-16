#include "structs_matrix.h"
#include "allocate.h"
#include "read.h"
#include "sp_matrix_create.h"
#include "fill_matrix.h"
#include "multiplication.h"
#include "print.h"
#include "measure_time.h"

size_t get_size_matrix_t(const matrix_t *matrix)
{
    return matrix->n * matrix->m * sizeof(int);
}
size_t get_size_sp_matrix_t(const special_matrix_t *matrix)
{
    return 2 * matrix->na *  sizeof(int) +
           (matrix->n + 1) * sizeof(int);
}
size_t get_size_sp_vector_t(const special_vector_column_t *vector)
{
    return vector->na *  sizeof(int) +
           (vector->n + 1) * sizeof(int);
}

void auto_measure_effinciency()
{
    printf("\nСравнения эффективности двух методов хранения матриц и их операции.\n");

    struct timeval tv_start, tv_stop;
    int64_t time_u = 0, time_s = 0, elapsed_u = 0, elapsed_s = 0;

    matrix_t matrix, vector, result;
    default_matrix_t(&matrix);
    default_matrix_t(&vector);
    default_matrix_t(&result);

    special_matrix_t sp_matrix;
    default_special_matrix_t(&sp_matrix);

    special_vector_column_t sp_vector, sp_result;
    default_special_vector_t(&sp_vector);
    default_special_vector_t(&sp_result);

    int rc = 1;
    printf("\nВажно! При вводе размера в качества размера для вектора столбца будет взято "
           "значение размера столбцов (m) для размера вектора столбца\n");
    while (rc != 0)
    {
        rc = read_matrix_size(&matrix.n, &matrix.m);
        if (rc != EXIT_SUCCESS)
            print_err_matrix(rc);
    }
    vector.n = matrix.m;
    vector.m = 1;
    matrix.matrix = allocate_matrix(matrix.n, matrix.m);
    vector.matrix = allocate_matrix(vector.n, vector.m);

    for (int percent = 0; percent <= 100; percent += STEP_PERCENT)
    {
        int non_zero_el_m = matrix.n * matrix.m * percent / 100;
        int non_zero_el_v = vector.n * vector.m * percent / 100;
        auto_fill(&matrix, non_zero_el_m);
        (void) create_special_matrix(&sp_matrix, &matrix);
        auto_fill(&vector, non_zero_el_v);
        (void) create_special_vector(&sp_vector, &vector);

        for (int i = 0; i < I_STEP; i++)
        {
            gettimeofday(&tv_start, NULL);
            (void) multiply_matrix(&result, &matrix, &vector);
            gettimeofday(&tv_stop, NULL);
            time_u = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        }
        elapsed_u /= (I_STEP - 2);

        size_t size_matrixs = get_size_matrix_t(&matrix) +
                              get_size_matrix_t(&vector) +
                              get_size_matrix_t(&result);
        free_matrix(result.matrix, result.n);
        default_matrix_t(&result);

        for (int i = 0; i < I_STEP; i++)
        {
            gettimeofday(&tv_start, NULL);
            (void) multiply_special_matrix(&sp_result, &sp_matrix, &sp_vector);
            gettimeofday(&tv_stop, NULL);
            time_s = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            elapsed_s+= time_s;
        }
        elapsed_s /= (I_STEP - 2);

        size_t size_sp_matrixs = get_size_sp_matrix_t(&sp_matrix) +
                                 get_size_sp_vector_t(&sp_vector) +
                                 get_size_sp_vector_t(&sp_result);

        print_measure(size_matrixs, size_sp_matrixs, elapsed_u, elapsed_s, percent);
        printf("Количество ненулевых элеметов в матрице: %d\n", non_zero_el_m);
        printf("Количество ненулевых элеметов в векторе-столбце: %d\n", non_zero_el_v);

        free_special_matrix(&sp_matrix);
        free_special_vector(&sp_vector);
        free_special_vector(&sp_result);
        default_special_matrix_t(&sp_matrix);
        default_special_vector_t(&sp_vector);
        default_special_vector_t(&sp_result);
    }

    free_matrix(matrix.matrix, matrix.n);
    default_matrix_t(&matrix);
    free_matrix(vector.matrix, vector.n);
    default_matrix_t(&vector);
}

void print_measure(size_t size_m, size_t size_r, int64_t time_m, int64_t time_r, int percent)
{
    printf("\nЗаполненность матриц на %d", percent);
    printf("\n┌───────────────┬─────────────────┬────────────────┐\n"
           "│      Метод    │ Размер в байтах │   Время в мс   │\n");
    printf("├───────────────┼─────────────────┼────────────────┤\n");
    printf("│   Основной    │ %-15zu │ %-14"PRId64" │\n", size_m, time_m);
    printf("│  Разреженный  │ %-15zu │ %-14"PRId64" │\n", size_r, time_r);
    printf("├───────────────┼─────────────────┼────────────────┤\n");
    if (time_m == 0 && time_r == 0)
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", 100.0 - (100.0 * size_r / size_m), 0.0);
    else if (time_r == 0)
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", 100.0 - (100.0 * size_r / size_m), 100.0);
    else if (time_m == 0)
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", 100.0 - (100.0 * size_r / size_m), -100.0);
    else
        printf("│    Процент    │ %-+15.1lf │ %-+14.1lf │\n", 100.0 - (100.0 * size_r / size_m), 100.0 - (100.0 * time_r / time_m));
    printf("└───────────────┴─────────────────┴────────────────┘\n");
}