#include "structs_matrix.h"
#include "errors.h"
#include "allocate.h"
#include "multiplication.h"

int multiply_matrix(matrix_t *result, matrix_t *matrix_1, matrix_t *matrix_2)
{
    if (matrix_1->m != matrix_2->n)
        return MULTY_ERR;
    result->n = matrix_1->n;
    result->m = matrix_2->m;
    result->matrix = allocate_matrix(result->n, result->m);
    if (!result->matrix)
        return MATRIX_MEMORY_ERR ;
    int el_multy = 0;
    for (int i = 0; i < result->n; i++)
        for (int j = 0; j < result->m; j++)
        {
            for (int k = 0; k < matrix_1->m; k++)
                el_multy += matrix_1->matrix[i][k] * matrix_2->matrix[k][j];
            result->matrix[i][j] = el_multy;
            el_multy = 0;
        }
    return 0;
}
int multiply_special_matrix(special_vector_column_t *result, special_matrix_t *matrix, special_vector_column_t *vector)
{
    if (matrix->m != vector->n)
        return MULTY_ERR;
    result->n = matrix->n;
    result->na = result->n;

    int rc = allocate_special_vector(result);
    if (rc != 0)
        return rc;

    int non_zero_el = 0, res_matrix_el;

    result->IA.list[0] = 0;
    int ia_ind = 0;
    for (unsigned short i = 0, j = 0; i < matrix->n; i++) {
        res_matrix_el = 0;
        if (matrix->IA.list[i + 1] != matrix->IA.list[i])
        {
            int k = matrix->IA.list[i];
            while (k < matrix->IA.list[i + 1]) {
                if (vector->IA.list[matrix->JA[j]] != vector->IA.list[matrix->JA[j] + 1])
                    res_matrix_el += matrix->A[j] * vector->A[vector->IA.list[matrix->JA[j]]];
                j++;
                k++;
            }
        }
        if (res_matrix_el != 0)
        {
            result->A[non_zero_el] = res_matrix_el;
            result->IA.list[ia_ind] = non_zero_el;
            non_zero_el++;
        }
        else
            result->IA.list[ia_ind] = non_zero_el;
        ia_ind++;
    }
    int *p;
    result->IA.list[ia_ind] = non_zero_el;
    result->na = non_zero_el;
    if (result->na == 0) {
        free(result->A);
        result->A = NULL;
    } else
    {
        p = realloc(result->A, result->na * sizeof(int));
        if (!p)
            return SP_RESULT_MEMORY_ERR;
        result->A = p;
    }
    p = realloc(result->IA.list, (result->n + 1) * sizeof(int));
    if (!p)
        return SP_RESULT_MEMORY_ERR;
    result->IA.list = p;
    return EXIT_SUCCESS;
}