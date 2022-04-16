#include "../inc/tree_struct.h"

#define N 10000
#define MAX_HEIGHT_SIZE 10

size_t get_rank(long long num)
{
    size_t result = 0;
    if (num != 0)
    {
        while (num != 0)
        {
            result++;
            num /= 10;
        }
    }

    return result;
}

void num_in_str(long long num, char *str)
{
    int rank = get_rank(num);
    size_t j = 0;

    int k = 0;

    if (num < 0)
        str[k++] = '-';

    for (; j < rank; j++)
    {
        long long tmp = 1;
        for (size_t l = 0; l < rank - j - 1; l++)
            tmp *= 10;

        if (num < 0)
            str[k++] = (char) ('0' - num / tmp);
        else if (num == 0)
            str[k++] = '0';
        else
            str[k++] = (char) ('0' + num / tmp);

        num %= tmp;
    }
    str[k] = '\0';
}

static void create_vertex_string(const branch_t *const vertex, char *buffer)
{
    if (vertex->right == NULL && vertex->left == NULL)
    {
        return;
    }

    char str_height[MAX_HEIGHT_SIZE];
    char str_num[MAX_HEIGHT_SIZE];

    num_in_str(vertex->number, str_num);
    strcat(buffer, str_num);
    buffer[strlen(buffer)] = ' ';

    if (vertex->left == NULL)
        strcat(buffer, "NULL");
    else
    {
        num_in_str(vertex->left->number, str_num);
        strcat(buffer, str_num);
    }
    buffer[strlen(buffer)] = ' ';

    if (vertex->right == NULL)
        strcat(buffer, "NULL");
    else
    {
        num_in_str(vertex->right->number, str_num);
        strcat(buffer, str_num);
    }
    buffer[strlen(buffer)] = ' ';

    sprintf(str_height, "%d", vertex->height);
    strcat(buffer, str_height);
    buffer[strlen(buffer)] = '_';

    if (vertex->right != NULL)
    {
        create_vertex_string(vertex->right, buffer);
    }

    if (vertex->left != NULL)
    {
        create_vertex_string(vertex->left, buffer);
    }
}

void print_tree(tree_t tree)
{
    char buffer[N] = "py ../src/painting.py \"";
    create_vertex_string(tree.head, buffer);
    buffer[strlen(buffer) - 1] = '\"'; //ASCII_APOSTROPHE;
    printf("%s\n", buffer);
    system(buffer);
}