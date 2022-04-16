#include "structs_matrix.h"
#include "errors.h"
#include "allocate.h"

int **allocate_matrix(int n, int m)
{
    int **data = malloc(n * sizeof(int *));
    if (!data)
        return NULL;
    for (size_t i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(int));
        if (!data[i])
        {
            free_matrix(data, n);
            return NULL;
        }
    }
    return data;
}
int allocate_special_matrix(special_matrix_t *special_matrix)
{
    special_matrix->A = malloc(special_matrix->na * sizeof(int));
    if (special_matrix->A == NULL)
        return A_ARR_MEMORY_ERR;
    special_matrix->JA = malloc(special_matrix->na * sizeof(int));
    if (special_matrix->JA == NULL)
    {
        free(special_matrix->A);
        special_matrix->A = NULL;
        return JA_ARR_MEMORY_ERR;
    }
    special_matrix->IA.list = malloc((special_matrix->n + 1) * sizeof(int));
    if (special_matrix->IA.list == NULL)
    {
        free(special_matrix->A);
        special_matrix->A = NULL;
        free(special_matrix->JA);
        special_matrix->JA = NULL;
        return IA_ARR_MEMORY_ERR;
    }
    return EXIT_SUCCESS;
}
int allocate_special_vector(special_vector_column_t *special_vector)
{
    special_vector->A = malloc(special_vector->na * sizeof(int));
    if (special_vector->A == NULL)
        return A_ARR_MEMORY_ERR;
    special_vector->IA.list = malloc((special_vector->n + 1) * sizeof(int));
    if (special_vector->IA.list == NULL)
    {
        free(special_vector->A);
        special_vector->A = NULL;
        return IA_ARR_MEMORY_ERR;
    }
    return EXIT_SUCCESS;
}

void free_matrix(int **data, int n)
{
    for (size_t i = 0; i < n; i++)
        free(data[i]);
    free(data);
}
void free_special_matrix(special_matrix_t *special_matrix)
{
    free(special_matrix->A);
    free(special_matrix->JA);
    free(special_matrix->IA.list);
}
void free_special_vector(special_vector_column_t *special_vector)
{
    free(special_vector->A);
    free(special_vector->IA.list);
}