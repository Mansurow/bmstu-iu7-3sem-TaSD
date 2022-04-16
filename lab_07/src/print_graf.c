#include "../inc/print_graf.h"

void print_graphviz_matrix(FILE *graph_visual, st_matrix *matrix) {
    if (matrix->matrix == NULL || !matrix->n)
        printf("Граф пуст!\n");
    else
    {
        fprintf(graph_visual, "digraph { \n\trankdir=LR; \n");

        int flag = 0;
        for (int i = 0; i < matrix->n; ++i) {
            for (int j = 0; j < matrix->n; ++j)
                if (matrix->matrix[i][j])
                    flag ++;

            if (!flag)
                fprintf(graph_visual, "\t%d [arrowhead=none]\n", i + 1);
            flag = 0;
        }

        for (int i = 0; i < matrix->n; ++i)
            for (int j = 0; j < matrix->n; j++)
                if (matrix->matrix[i][j] && (i < j || !matrix->matrix[j][i]))
                    fprintf(graph_visual, "\t%d -> %d[label=%d][arrowhead=none]\n", i + 1, j + 1, matrix->matrix[i][j]);

        fprintf(graph_visual, "%s", "}");
    }
}

void print_matrix(const st_matrix *graf)
{
    if (graf->matrix == NULL || !graf->n)
        printf("Граф пуст!\n");
    else
    {
        for (int i = 0; i < graf->n; i++) {
            for (int j = 0; j < graf->n; j++)
                printf("%3d ", graf->matrix[i][j]);
            printf("\n");
        }
    }
}

void print_graphviz_list(FILE *graph_visual, const st_array_list *graf)
{
    if (graf->array == NULL || !graf->n)
        printf("Граф пуст!\n");
    else
    {
        fprintf(graph_visual, "digraph { \n\trankdir=LR; \n");

        int flag = 0;
        for (int i = 0; i < graf->n; ++i) {
            if (!*(graf->array + i))
                fprintf(graph_visual, "\t%d [arrowhead=none]\n", i + 1);
            flag = 0;
        }

        for (int i = 0; i < graf->n; ++i)
        {
            st_list *current = *(graf->array + i);
            for (; current; current = current->next)
                if (current->top > i + 1)
                    fprintf(graph_visual, "\t%d -> %d[label=%d][arrowhead=none]\n", i + 1, current->top, current->weight);

        }
        fprintf(graph_visual, "%s", "}");
    }
}

void print_list(st_list *head)
{
    for (; head; head = head->next) {
        if (head->next)
            printf("|%2d|-(%3d)->", head->top, head->next->weight);
        else
            printf("|%2d|", head->top);
    }
    printf("\n");
}

void print_array_list(const st_array_list *graf)
{
    if (!graf->n || graf->array == NULL)
        printf("Граф пуст!\n");
    else
        for (int i = 0; i < graf->n; i++)
        {
            if (*(graf->array + i))
            {
                printf("|%2d|-(%3d)->", i + 1, (*(graf->array + i))->weight);
                print_list(*(graf->array + i));
            } else
                printf("|%2d|\n", i + 1);
        }

}