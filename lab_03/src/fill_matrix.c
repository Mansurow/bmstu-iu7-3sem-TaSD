#include "structs_matrix.h"
#include "errors.h"
#include "allocate.h"
#include "read.h"
#include "print.h"
#include "fill_matrix.h"

void default_matrix_t(matrix_t *matrix)
{
    matrix->n = 0;
    matrix->m = 0;
    matrix->matrix = NULL;
}
void default_special_matrix_t(special_matrix_t *sp_matrix)
{
    sp_matrix->n = 0;
    sp_matrix->m = 0;
    sp_matrix->na = 0;
    sp_matrix->JA = NULL;
    sp_matrix->A = NULL;
    sp_matrix->IA.list = NULL;
}
void default_special_vector_t(special_vector_column_t *sp_vector)
{
    sp_vector->n = 0;
    sp_vector->na = 0;
    sp_vector->A = NULL;
    sp_vector->IA.list = NULL;
}

void fill_matrix(int **matrix, int n, int m, int fill)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            matrix[i][j] = fill;
}

void auto_fill_matrix(matrix_t *matrix)
{
    int rc = 1;
    int percent = 0;
    while (rc != 0)
    {
        rc = read_matrix_size(&matrix->n, &matrix->m);
        if (rc != EXIT_SUCCESS)
            print_err_matrix(rc);
    }
    rc = 1;
    while (rc != 0)
    {
        rc = read_auto_percent(&percent);
        if (rc != EXIT_SUCCESS)
            print_err_matrix(rc);
    }
    int non_zero_el = matrix->n * matrix->m * percent / 100;
    printf("Количество ненулевых элементов (от 0 до %d): %d\n", matrix->n * matrix->m, non_zero_el);
    matrix->matrix = allocate_matrix(matrix->n, matrix->m);
    for (int i = 0; i < matrix->n; i++)
        for (int j = 0; j < matrix->m; j++)
            matrix->matrix[i][j] = 0;
    for (int i = 0, ii = 0, jj = 0, el = 0; i < non_zero_el;)
    {
        ii = rand() % matrix->n;
        jj = rand() % matrix->m;
        el = -100 + rand() % MAX_NUMBER;
        if (matrix->matrix[ii][jj] == 0 && el != 0)
        {
            matrix->matrix[ii][jj] = el;
            i++;
        }
    }
}
void auto_fill_vector_column(matrix_t *matrix)
{
    int rc = 1;
    int percent = 0;
    matrix->m = 1;
    while (rc != 0)
    {
        rc = read_size_vector_column(&matrix->n);
        if (rc != EXIT_SUCCESS)
            print_err_matrix(rc);
    }
    rc = 1;
    while (rc != 0)
    {
        rc = read_auto_percent(&percent);
        if (rc != EXIT_SUCCESS)
            print_err_matrix(rc);
    }
    int non_zero_el = matrix->n * matrix->m * percent / 100;
    printf("Количество ненулевых элементов (от 0 до %d): %d\n", matrix->n * matrix->m, non_zero_el);
    matrix->matrix = allocate_matrix(matrix->n, matrix->m);
    for (int i = 0; i < matrix->n; i++)
        matrix->matrix[i][0] = 0;
    for (int i = 0, ii = 0, el = 0; i < non_zero_el;)
    {
        ii = rand() % matrix->n;
        el = -100 + rand() % MAX_NUMBER;
        if (matrix->matrix[ii][0] == 0 && el != 0)
        {
            matrix->matrix[ii][0] = el;
            i++;
        }
    }
}
void auto_fill(matrix_t *matrix, int non_zero_el)
{
    for (int i = 0; i < matrix->n; i++)
        for (int j = 0; j < matrix->m; j++)
            matrix->matrix[i][j] = 0;
    for (int i = 0, ii = 0, jj = 0, el = 0; i < non_zero_el;)
    {
        ii = rand() % matrix->n;
        jj = rand() % matrix->m;
        el = 1 + rand() % MAX_NUMBER;
        if (matrix->matrix[ii][jj] == 0 && el != 0)
        {
            matrix->matrix[ii][jj] = el;
            i++;
        }
    }
}