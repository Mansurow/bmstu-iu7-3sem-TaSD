#include "../inc/memory_graf.h"

void default_matrix_graf(st_matrix *graf)
{
    graf->matrix = NULL;
    graf->n = 0;
}

void default_list_graf(st_array_list *graf)
{
    graf->array = NULL;
    graf->n = 0;
}

st_list *top_create(int top, int weight)
{
    st_list *node= malloc(sizeof(st_list));
    if (node != NULL)
    {
        node->top = top;
        node->weight = weight;
        node->next = NULL;
    }

    return node;
}

st_list **alocate_array_list(size_t n)
{
    st_list **data = NULL;
    if (n > 0)
    {
        data = malloc(n * sizeof(st_list *));
        for (int i = 0; i < n; i++)
            *(data + i) = NULL;
    }

    return data;
}

int list_push(st_list **head, int top, int weight)
{
    int rc = EXIT_SUCCESS;
    st_list *node = top_create(top, weight);
    if (node != NULL)
    {
        st_list *tail = *head;
        //if (tail != NULL)
        //    for (; tail->next; tail = tail->next);
        if (tail != NULL)
            for (; tail->next; tail = tail->next);
        if (*head == NULL)
            *head = node;
        else
            tail->next = node;
        tail = node;
        // в начало
        //node->next = *head;
        //*head = node;
    }
    else
        rc = MEMORY_ERROR;

    return rc;
}

void free_list(st_list **head)
{
    if (head != NULL && *head != NULL)
    {
        st_list *current;
        for (; *head; *head = current)
        {
            current = (*head)->next;
            free(*head);
        }
        current = NULL;
        *head = NULL;
    }
}

void free_array_list(st_array_list *graf)
{
    if (graf != NULL && graf->array != NULL)
    {
        for (int i = 0; i < graf->n; i++)
            free_list((graf->array + i));
        free(graf->array);
        graf->array = NULL;
        graf->n = 0;
    }
}

void free_matrix(int ***matrix, size_t n)
{
    if (matrix != NULL && *matrix != NULL && n)
    {
        for (int i = 0; i < n; i++)
            free((*matrix + i));
        free(*matrix);
        *matrix = NULL;
    }
}

int **allocate_matrix(size_t n, size_t m)
{
    int **matrix = NULL;
    if (n > 0 && m > 0)
    {
        matrix = calloc(n, sizeof(int *));
        if (matrix != NULL)
            for (int i = 0; i < n; i++)
            {
                matrix[i] = calloc(m, sizeof(int));
                if (matrix[i] == NULL)
                    free_matrix(&matrix, n);
            }
    }

    return matrix;
}

