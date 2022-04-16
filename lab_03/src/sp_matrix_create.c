#include "structs_matrix.h"
#include "errors.h"
#include "allocate.h"
#include "sp_matrix_create.h"

int get_zero_element(int **matrix, int n, int m)
{
    int count = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (matrix[i][j] != 0)
                count++;
    return count;
}
int create_special_matrix(special_matrix_t *special_matrix, const matrix_t *matrix)
{
    int rc = EXIT_SUCCESS;
    if (matrix->n < MIN_N || matrix->n > MAX_N)
        rc = MATRIX_N_ERR;
    else if (matrix->m < MIN_M || matrix->m > MAX_M)
        rc = MATRIX_N_ERR;
    else
    {
        special_matrix->n = matrix->n;
        special_matrix->m = matrix->m;
        int non_zero_el = get_zero_element(matrix->matrix, matrix->n, matrix->m);
        special_matrix->na = non_zero_el;
        rc = allocate_special_matrix(special_matrix);
        if (rc == EXIT_SUCCESS)
        {
            special_matrix->IA.list[0] = 0;
            for (int i = 0, curr_a = 0, curr_ia = 1; i < matrix->n; i++) {
                for (int j = 0; j < matrix->m; j++)
                {
                    if (matrix->matrix[i][j] != 0) {
                        special_matrix->A[curr_a] = matrix->matrix[i][j];
                        special_matrix->JA[curr_a] = j;
                        curr_a++;
                    }
                }
                special_matrix->IA.list[curr_ia] = curr_a;
                curr_ia++;
            }
            special_matrix->IA.list[special_matrix->n] = special_matrix->na;
        }
    }
    return rc;
}
int create_special_vector(special_vector_column_t *special_vector, const matrix_t *matrix)
{
    int rc = EXIT_SUCCESS;
    if (matrix->n < MIN_N || matrix->n > MAX_N)
        rc = MATRIX_N_ERR;
    else
    {
        special_vector->n = matrix->n;
        int non_zero_el = get_zero_element(matrix->matrix, matrix->n, matrix->m);
        special_vector->na = non_zero_el;
        rc = allocate_special_vector(special_vector);
        if (rc == EXIT_SUCCESS)
        {
            special_vector->IA.list[0] = 0;
            for (int i = 0, curr_a = 0, curr_ia = 1; i < matrix->n; i++) {
                if (matrix->matrix[i][0] != 0)
                {
                    special_vector->A[curr_a] = matrix->matrix[i][0];
                    curr_a++;
                }
                special_vector->IA.list[curr_ia] = curr_a;
                curr_ia++;
            }
        }
    }
    return rc;
}

int create_usual_matrix(int ***matrix, int n, int m)
{
    int rc = EXIT_SUCCESS;
    int **p = allocate_matrix(n, m);
    if (!p)
        rc = MATRIX_MEMORY_ERR;
    else
        *matrix = p;
    return rc;
}