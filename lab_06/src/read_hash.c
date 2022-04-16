#include "../inc/hash_struct.h"

void default_hash(hash_table_t *hash)
{
    hash->array = NULL;
    hash->size = 0;
    hash->divider = 0;
    hash->compare = 0;
    hash->total_compare = 0;
    hash->elements = 0;
}

int fread_hash(FILE *f, hash_table_t *hash_table)
{
    int rc = EXIT_SUCCESS;

    if (f == NULL)
        rc = PARAMS_ERR;
    else
    {
        int num, result, count = 0;

        if (hash_table->divider == 0)
        {
            while (fscanf(f, "%d", &num) == 1) count++;

            hash_table->divider = select_prime(count);

            hash_table->array = malloc(hash_table->divider * sizeof(hash_elem_t));
            hash_table->size = hash_table->divider;
            for (int i = 0; i < hash_table->size; i++) {
                hash_table->array[i].number = 0;
                hash_table->array[i]._is_full = '0';
            }
            rewind(f);
        }

        while (!rc && result != -1)
        {
            if ((result = fscanf(f, "%d", &num)) != 1)
            {
                if (result == 0)
                    rc = INVALID_ERR;
                else
                    rc = EXIT_SUCCESS;
            }
            else
            {
                rc = push_hash(hash_table, num);
                if (rc == ITEM_EXISTS)
                    rc = EXIT_SUCCESS;
            }
        }
    }

    return rc;
}
