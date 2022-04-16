#include "../inc/hash_struct.h"

int search_hash(hash_table_t *hash_table, int search)
{
    int cmp = 1;
    int index = hash_func(search, hash_table->divider);
    if (hash_table->array[index]._is_full == '1' && hash_table->array[index].number == search)
        return cmp;
    else if (hash_table->array[index]._is_full == '1' && hash_table->array[index].number != search)
    {
        while (hash_table->array[index]._is_full == '1' && hash_table->array[index].number != search && cmp)
        {
            cmp++;
            index++;
            if (index == hash_table->size)
                cmp = 0;
        }
    }
    return cmp;
}