#include "../inc/read_graf.h"

int get_row(FILE *f, size_t *row)
{
    int size = 0, rc = EXIT_SUCCESS;
    char ch, prev = ' ';
    while ((ch = fgetc(f)) != EOF && ch != '\n')
    {
        if (isdigit(ch)) {
            if (!isdigit(prev))
                size++;
        }
        else if (!iscntrl(ch) && !isspace(ch))
            rc = EXIT_FAILURE;
        prev = ch;
    }

    if (rc == EXIT_SUCCESS)
        *row = size;
    else
        *row = 0;

    rewind(f);
    return rc;
}

int get_column(FILE *f, size_t *column)
{
    int rc = EXIT_SUCCESS, size = 0;
    char str = ' ', prev = str;
    if (f == NULL)
        rc == EXIT_FAILURE;
    else
        while (str != EOF)
        {
            str = fgetc(f);
            if (str == '\n' || (str == EOF && prev != '\n'))
                size++;
            prev = str;
        }


    if (size < 1)
        rc = EXIT_FAILURE;
    else
        *column = size;

    rewind(f);
    return rc;
}

int read_file_matrix(FILE *f, st_matrix *graf)
{
    int rc = EXIT_SUCCESS, num;
    size_t n, m;
    rc = get_column(f, &n);
    if (rc == EXIT_SUCCESS)
        rc = get_row(f, &m);
    if (rc == EXIT_SUCCESS) {
        if (n != m)
            rc = NOT_SQUERE_MATRIX;
        else
        {
            graf->matrix = allocate_matrix(n, m);
            if (graf->matrix != NULL)
            {
                graf->n = n;
                for (int i = 0; i < graf->n && !rc; i++)
                    for (int j = 0; j < graf->n && !rc; j++) {
                        if (fscanf(f, "%d", &num) == 1 && (num >= 0))
                            graf->matrix[i][j] = num;
                        else
                            rc = INVALID_ERR;
                    }
            }
        }

    }

    return rc;
}

int read_file_list(FILE *f, st_array_list *graf)
{
    int rc = EXIT_SUCCESS, num;
    size_t n, m;
    rc = get_column(f, &n);
    if (rc == EXIT_SUCCESS)
        rc = get_row(f, &m);
    if (rc == EXIT_SUCCESS) {
        if (n != m)
            rc = NOT_SQUERE_MATRIX;
        else
        {
            graf->array = alocate_array_list(n);
            if (graf->array != NULL)
            {
                graf->n = n;
                for (int i = 0; i < graf->n; ++i) {
                    st_list *current = *(graf->array + i);
                    for (int j = 0; j < graf->n; ++j) {
                        if (fscanf(f, "%d", &num) == 1 && num > 0) {
                            rc = list_push(&current, j + 1, num);
                            if (rc == EXIT_SUCCESS)
                                *(graf->array + i) = current;
                         }
                        else if (num != 0)
                            rc = EXIT_FAILURE;
                    }
                }
            }
        }
    }

    return rc;
}