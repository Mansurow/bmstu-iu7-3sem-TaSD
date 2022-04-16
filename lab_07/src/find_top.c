#include "../inc/find_top.h"

#define BIG 1000000000

int algoritm_ballman_fold_matrix(const  st_matrix *graf, int start_top, int *distance)
{
    int rc = EXIT_SUCCESS;
    if (graf == NULL)
        rc = GRAF_ERR;
    else if (graf->matrix == NULL || graf->n <= 0)
        rc = MATRIX_EMPTY;
    else if (start_top <= 0 || start_top > graf->n)
        rc = NOT_TOP_ERR;
    else
    {
        for (int i = 0; i < graf->n; i++)
            distance[i] = BIG;

        distance[start_top - 1] = 0;
        for (int k = 0; k < graf->n; k++)
            for (int i = 0; i < graf->n; i++)
                for (int j = 0; j< graf->n; j++)
                    if (graf->matrix[i][j] != 0)
                        if (distance[j] > distance[i] + graf->matrix[i][j])
                            distance[j] = distance[i] + graf->matrix[i][j];
    }

    return rc;
}

int algoritm_dijkstra_matrix(const st_matrix *graf, int start_top, int *distance)
{
    int rc = EXIT_SUCCESS;
    if (graf == NULL)
        rc = GRAF_ERR;
    else if (graf->matrix == NULL || graf->n <= 0)
        rc = MATRIX_EMPTY;
    else if (start_top <= 0 || start_top > graf->n)
        rc = NOT_TOP_ERR;
    else
    {
        int S[graf->n];
        for (int i = 0; i < graf->n; i++)
        {
            distance[i] = BIG;
            S[i] = 0;
        }
        distance[start_top - 1] = 0;
        int min, w;
        do
        {
            min = w = BIG;
            for (int i = 0; i < graf->n; i++)
            {
                if (!S[i] && distance[i] < min)
                {
                    w = i;
                    min = distance[i];
                }
            }

            if (w != BIG)
            {
                for (int i = 0; i < graf->n; i++)
                {
                    if (graf->matrix[w][i])
                    {
                        int temp = min + graf->matrix[w][i];
                        if (temp < distance[i])
                            distance[i] = temp;
                    }
                }

                S[w] = w + 1;
            }
        } while (w < BIG);
    }
    return rc;
}

int algoritm_dijkstra_list(const st_array_list *graf, int start_top, int *distance)
{
    int rc = EXIT_SUCCESS;
    if (graf == NULL)
        rc = GRAF_ERR;
    else if (graf->array == NULL || graf->n <= 0)
        rc = ARRAY_EMPTY;
    else if (start_top <= 0 || start_top > graf->n)
        rc = NOT_TOP_ERR;
    else
    {
        int S[graf->n];
        for (int i = 0; i < graf->n; i++)
        {
            distance[i] = BIG;
            S[i] = 0;
        }

        distance[start_top - 1] = 0;
        int min, w;
        do
        {
            min = w = BIG;
            for (int i = 0; i < graf->n; i++)
            {
                if (!S[i] && distance[i] < min)
                {
                    w = i;
                    min = distance[i];
                }
            }

            if (w != BIG)
            {
                st_list *current = *(graf->array + w);
                for (int i = 0; current; i++)
                {
                    if (i + 1 == current->top)
                    {
                        int temp = min + current->weight;
                        if (temp < distance[i])
                            distance[i] = temp;
                        current = current->next;
                    }
                }

                S[w] = w + 1;
            }
        } while (w < BIG);

    }

    return rc;
}

int algoritm_ballman_fold_list(const st_array_list *graf, int start_top, int *distance)
{
    int rc = EXIT_SUCCESS;
    if (graf == NULL)
        rc = GRAF_ERR;
    else if (graf->array == NULL || graf->n <= 0)
        rc = ARRAY_EMPTY;
    else if (start_top <= 0 || start_top > graf->n)
        rc = NOT_TOP_ERR;
    else
    {
        for (int i = 0; i < graf->n; i++)
            distance[i] = BIG;

        distance[start_top - 1] = 0;
        for (int k = 0; k < graf->n; k++)
            for (int i = 0; i < graf->n; i++)
                if (*(graf->array + i))
                {
                    st_list *current = *(graf->array + i);
                    for (int j = 0; current; j++)
                        if (j + 1 == current->top)
                        {
                            if (distance[j] > distance[i] + current->weight)
                                distance[j] = distance[i] + current->weight;
                            current = current->next;
                        }
                }
    }
}

void print_top_as_input(int *distance, int size, int max_way, int start_top)
{
    int flag = 0;
    printf("Вершины, чей минимальный путь не длинее %d:\n", max_way);
    for (int i = 0; i < size; i++)
        if (distance[i] <= max_way) {
            printf("    %d ~> %d: %d\n", start_top, i + 1, distance[i]);
            flag = 1;
        }
    if (!flag)
        printf("   Путь от вершины %d до остальных длинее, чем %d\n", start_top, max_way);

    flag = 0;
    printf("Вершины, чей минимальный путь длинее %d:\n", max_way);
    for (int i = 0; i < size; i++)
        if (distance[i] > max_way && distance[i] != BIG) {
            printf("    %d ~> %d: %d\n", start_top, i + 1, distance[i]);
            flag = 1;
        }
    if (!flag)
        printf("   Путь от вершины %d до остальных не длинее, чем %d\n", start_top, max_way);

}