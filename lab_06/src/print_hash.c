#include "../inc/hash_struct.h"

void print_hash(hash_table_t *table)
{
    if (table->elements == 0)
    {
        printf("\x1B[36mХеш-таблица пуста\x1B[0m\n\n");
        return;
    }

    printf("\x1B[33mИндекс | Элемент\x1B[0m\n\n");

    for (int i = 0; i < table->size; i++)
    {
        if (table->array[i]._is_full == '1')
            printf("\x1B[36m%3d | %3d\x1B[0m\n", i, table->array[i].number);
        else
            printf("%3d |  -\n", i);
    }

    printf("\n\x1B[33mСреднее кол-во сравнений для нахождения нужного элемента в таблице:"
           " %.3f\x1B[0m\n\n", (double) table->total_compare / table->elements);

}

