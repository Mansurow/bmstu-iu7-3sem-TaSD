#include "structs_matrix.h"
#include "errors.h"
#include "fill_matrix.h"
#include "allocate.h"
#include "read.h"
#include "print.h"
#include "sp_matrix_create.h"

int input_step_menu(int *step, int min, int max)
{
    int rc = EXIT_SUCCESS;
    char buff[8];
    if (scanf("%d", step) != 1) {
        rc = INVALID_ERR;
        fgets(buff, sizeof(buff), stdin);
    }
    else if (*step < min || *step > max)
        rc = STEP_ERR;
    return rc;
}

int read_matrix_size(int *n, int *m)
{
    int rc = EXIT_SUCCESS;
    char buff[8];
    printf("\nВведите количество строк и столбцов матрицы (от %d до %d) (n x m): ", MIN_N, MAX_N);
    if (scanf("%d %d", n, m) != 2) {
        rc = INVALID_ERR;
        fgets(buff, sizeof(buff), stdin);
    }
    else if (*n < MIN_N || *n > MAX_N)
        rc = MATRIX_N_ERR;
    else if (*m < MIN_M || *m > MAX_M)
        rc = MATRIX_M_ERR;
    return rc;
}
int read_size_vector_column(int *n)
{
    int rc = EXIT_SUCCESS;
    char buff[8];
    printf("Введите количество элементов вектора-столбца (от %d до %d) (n): ", MIN_N, MAX_N);
    if (scanf("%d", n) != 1)
    {
        rc = INVALID_ERR;
        fgets(buff, sizeof(buff), stdin);
    }
    else if (*n < MIN_N ||*n > MAX_N)
        rc = MATRIX_N_ERR;
    return rc;
}
int read_auto_percent(int *percent)
{
    int rc = EXIT_SUCCESS;
    char buff[8];
    printf("Введите процент заполнения матрицы (0 до 100): ");
    if (scanf("%d", percent) != 1) {
        rc = INVALID_ERR;
        fgets(buff, sizeof(buff), stdin);
    }
    else if (*percent < 0 || *percent > 100)
        rc = PERCENT_ERR;
    return rc;
}

int read_usual_matrix_element(int **matrix, int n, int m)
{
    int rc = EXIT_SUCCESS;
    for (int i = 0; i < n && rc == 0; i++)
        for (int j = 0; j < m && rc == 0; j++)
            if (scanf("%d", &matrix[i][j]) != 1)
                rc = INVALID_ERR;
    return rc;
}

int read_non_zero_elements(int *count, int n, int m)
{
    int rc = EXIT_SUCCESS;
    int non_zero_el = 0;
    char buff[8];
    printf("Введите количество ненулевых элементов (от 0 до %d): ", n * m);
    if (scanf("%d", &non_zero_el) != 1) {
        rc = INVALID_ERR;
        fgets(buff, sizeof(buff), stdin);
    }
    else if (non_zero_el < 0 ||
             non_zero_el > n * m)
        rc = NON_ZERO_ERR;
    else
        *count = non_zero_el;
    return rc;
}
void read_special_matrix_element(int **matrix, int n, int m, int non_zero_el)
{
    int rc = 0;
    fill_matrix(matrix, n, m, 0);
    printf("\nВведите ненулевой элемент (элемент i j):\n");
    for (int i = 0, ii = 0, jj = 0, el = 0; i < non_zero_el;)
    {
        if (scanf("%d%d%d", &el, &ii, &jj) != 3)
            rc = INVALID_ERR;
        else if (ii < 0 || jj < 0 || ii > n - 1 || jj > m - 1)
            rc = INDEX_NEGATIVE;
        else if (el == 0)
            rc = NON_ZERO_EL_ERR;
        else
        {
            if (matrix[ii][jj] == 0)
            {
                matrix[ii][jj] = el;
                i++;
            }
            else
                rc = INDEX_NON_ZERO_ERR;
        }
        if (rc != EXIT_SUCCESS)
        {
            print_err_matrix(rc);
            rc = 0;
        }
    }
}
void read_special_vector_column_element(int **matrix, int n, int non_zero_el)
{
    int rc = EXIT_SUCCESS;
    fill_matrix(matrix, n, 1, 0);
    printf("\nВведите ненулевой элемент (элемент i):\n");
    for (int i = 0, ii = 0, el = 0; i < non_zero_el;)
    {
        if (scanf("%d%d", &el, &ii) != 2)
            rc = INVALID_ERR;
        else if (ii < 0 || ii > n - 1)
            rc = INDEX_NEGATIVE;
        else if (el == 0)
            rc = NON_ZERO_EL_ERR;
        else
        {
            if (matrix[ii][0] == 0)
            {
                matrix[ii][0] = el;
                i++;
            }
            else
                rc = INDEX_NON_ZERO_ERR;
        }
        if (rc != EXIT_SUCCESS)
        {
            print_err_matrix(rc);
            rc = 0;
        }
    }
}

int read_usual_matrix_t (matrix_t *matrix)
{
    int rc = 1;
    char buff[8];
    while (rc != 0)
    {
        rc = read_matrix_size(&matrix->n, &matrix->m);
        if (rc != 0)
            print_err_matrix(rc);
    }
    if (rc == EXIT_SUCCESS)
    {
        rc = 1;
        while (rc != 0)
        {
            rc = create_usual_matrix(&matrix->matrix, matrix->n, matrix->m);
            if (rc == EXIT_SUCCESS) {
                printf("\nВведите элементы матрицы %d x %d:\n", matrix->n, matrix->m);
                rc = read_usual_matrix_element(matrix->matrix, matrix->n, matrix->m);
                if (rc != EXIT_SUCCESS)
                {
                    printf("\nМатрица заполнена безуспешно.\n");
                    free_matrix(matrix->matrix, matrix->n);
                    matrix->matrix = NULL;
                    print_err_matrix(rc);
                    fgets(buff, sizeof(buff), stdin);
                }
            }
        }
    }
    return rc;
}
int read_special_matrix_t(matrix_t *matrix)
{
    int rc = 1;
    while (rc != 0)
    {
        rc = read_matrix_size(&matrix->n, &matrix->m);
        if (rc != 0)
            print_err_matrix(rc);
    }
    if (rc == EXIT_SUCCESS)
    {
        rc = 1;
        int non_zero_el = 0;
        while (rc != 0)
        {
            rc = read_non_zero_elements(&non_zero_el, matrix->n, matrix->m);
            if (rc ==EXIT_SUCCESS)
            {
                rc = create_usual_matrix(&matrix->matrix, matrix->n, matrix->m);
                if (rc == EXIT_SUCCESS)
                    read_special_matrix_element(matrix->matrix, matrix->n, matrix->m, non_zero_el);
            } else
                printf("Ошибка! Количество введено не верно!");
        }
    }
    return rc;
}

int read_usual_vector_column(matrix_t *matrix)
{
    int rc = 1;
    char buff[8];
    while (rc != 0)
    {
        rc = read_size_vector_column(&matrix->n);
        if (rc != 0)
            print_err_matrix(rc);
    }
    if (rc == EXIT_SUCCESS)
    {
        matrix->m = 1;
        rc = 1;
        while (rc != 0)
        {
            rc = create_usual_matrix(&matrix->matrix, matrix->n, matrix->m);
            if (rc == EXIT_SUCCESS) {
                printf("\nВведите элементы вектора-столбца (%d) :\n", matrix->n);
                rc = read_usual_matrix_element(matrix->matrix, matrix->n, matrix->m);
                if (rc != EXIT_SUCCESS)
                {
                    printf("\nВектор-столбец заполнен безуспешно.");
                    free_matrix(matrix->matrix, matrix->n);
                    matrix->matrix = NULL;
                    print_err_matrix(rc);
                    fgets(buff, sizeof(buff), stdin);
                }
            }
        }
    }
    return rc;
}
int read_special_vector_column(matrix_t *matrix)
{
    int rc = 1;
    while (rc != 0)
    {
        rc = read_size_vector_column(&matrix->n);
        if (rc != 0)
            print_err_matrix(rc);
    }
    if (rc == EXIT_SUCCESS)
    {
        rc = 1;
        int non_zero_el = 0;
        while (rc != 0)
        {
            matrix->m = 1;
            rc = read_non_zero_elements(&non_zero_el, matrix->n, matrix->m);
            if (rc ==EXIT_SUCCESS)
            {
                rc = create_usual_matrix(&matrix->matrix, matrix->n, matrix->m);
                if (rc == EXIT_SUCCESS)
                    read_special_vector_column_element(matrix->matrix, matrix->n, non_zero_el);
            } else
                printf("Ошибка! Количество введено не верно!");
        }
    }
    return rc;
}