#include "../inc/hash_struct.h"

int pop_hash(hash_table_t *hash_table, int num)
{
    int rc = EXIT_SUCCESS;
    hash_table->compare = 0;
    if (hash_table != NULL && hash_table->array != NULL)
    {
        int index = num % hash_table->divider;
        for (int i = index; i < hash_table->size && !rc; i++)
        {
            hash_table->compare++;
            if (hash_table->array[i]._is_full == '1' && hash_table->array[i].number == num)
            {
                hash_table->elements--;
                hash_table->array[i]._is_full = '0';
                rc = ITEM_DELETE;
            }
        }
    }
    return rc;
}