#include "../inc/tree_struct.h"

void default_tree(tree_t *tree)
{
    tree->head = NULL;
    tree->size = 0;
    tree->total_compare = 0;
}

int fread_tree(FILE *f, tree_t *tree, _Bool _isbalance)
{
    int rc = EXIT_SUCCESS;

    if (f == NULL)
        rc = PARAMS_ERR;
    else
    {
        int num, result;
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
                rc = push_tree(&tree->head, num, _isbalance);
                if (rc == ITEM_EXISTS)
                    rc = EXIT_SUCCESS;
                if (rc == EXIT_SUCCESS) {
                    tree->size++;
                    if (tree->size >= 0)
                        tree->total_compare += search_element(tree->head, num);
                }
            }
        }
    }

    return rc;
}
