#include "../inc/hash_struct.h"

hash_table_t restruct(hash_table_t table, int search, int max)
{
    hash_table_t new_table;
    int cmp;
    int index;
    new_table.array = NULL;
    new_table.size = table.size;
    new_table.divider = table.divider;
    new_table.elements = table.elements;
    new_table.total_compare = 0;

    hash_elem_t *new_tmp = NULL;
    do
    {
        new_table.size += SHIFT;
        new_table.divider = select_prime(new_table.size);

        new_tmp = realloc(new_table.array, new_table.size * sizeof(hash_elem_t));
        if (new_tmp)
        {

            for (int i = 0; i < new_table.size; i++) {
                new_tmp[i].number = 0;
                new_tmp[i]._is_full = '0';
            }


            for (int i = 0; i < table.size; ++i)
            {
                if (table.array[i]._is_full == '1')
                {
                    index = hash_func(table.array[i].number, new_table.divider);

                    if (new_tmp[index]._is_full == '1')
                    {
                        while ((new_tmp[index]._is_full) == '1')
                        {
                            if (index == new_table.size) {
                                new_tmp = realloc(new_table.array, (++new_table.size) * sizeof(hash_elem_t));
                            }
                            index++;
                            new_table.total_compare++;
                        }
                        new_tmp[index].number = table.array[i].number;
                        new_tmp[index]._is_full = '1';
                    }
                    else
                    {
                        new_table.total_compare++;
                        new_tmp[index].number = table.array[i].number;
                        new_tmp[index]._is_full = '1';
                    }
                }
            }
            new_table.array = new_tmp;
        }
        cmp = search_hash(&new_table, search);
    } while (cmp > max);
    new_table.compare = cmp;
    return new_table;
}