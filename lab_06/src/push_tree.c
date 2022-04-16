#include "../inc/tree_struct.h"

int push_tree(branch_t **head, int number, _Bool _is_balance)
{
    int rc = EXIT_SUCCESS;
    if (head != NULL)
    {
        branch_t *new_head = *head;
        if(!new_head)
        {
            new_head = create_element_tree(number);
            if (!new_head)
                rc = MEMORY_ERR;
        } else
        {
            if(number < new_head->number)
                rc = push_tree(&new_head->left, number, _is_balance);
            else if (number > new_head->number)
                rc = push_tree(&new_head->right, number, _is_balance);
            else
                rc = ITEM_EXISTS;
        }

        if (rc == EXIT_SUCCESS) {
            if (_is_balance)
                new_head = balance_branch(new_head);
            else
                fixheight(new_head);
            *head = new_head;
        }
    }

    return rc;
}
