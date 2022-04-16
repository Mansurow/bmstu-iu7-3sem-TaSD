#include "../inc/hash_struct.h"

int push_hash(hash_table_t *hash_table, int num) {
    int rc = EXIT_SUCCESS;

    int index, compare = 1;
    if (!hash_table->array) {
        hash_table->divider = hash_table->size = rand() % 20 + 5;
        hash_table->array = malloc(hash_table->size * sizeof(hash_elem_t));
        for (int i = 0; i < hash_table->size; i++)
            hash_table->array[i]._is_full = '0';
    }
    index = hash_func(num, hash_table->divider);

    while ((!hash_table->array || hash_table->array[index]._is_full == '1') && !rc)
    {
        if (++index >= hash_table->size)
        {
            hash_elem_t *p = realloc(hash_table->array, (++hash_table->size) * sizeof(hash_elem_t));
            if (p == NULL)
                rc = MEMORY_ERR;
            else
            {
                hash_table->array = p;
                hash_table->array[index]._is_full = '0';
            }
        } else if (hash_table->array[index]._is_full == '1' && hash_table->array[index].number == num)
        {
            rc = ITEM_EXISTS;
        }
        compare++;
    }

    if (rc == EXIT_SUCCESS)
    {
        hash_table->array[index].number = num;
        hash_table->array[index]._is_full = '1';
        hash_table->elements++;
        hash_table->compare = compare;
        hash_table->total_compare += compare;
    } else
        hash_table->compare = 0;

    return rc;
}