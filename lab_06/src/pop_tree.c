#include "../inc/tree_struct.h"

branch_t *findmin(branch_t *head)
{
    branch_t *result = NULL;
    if (head != NULL)
    {
        if (head->left)
            result = findmin(head->left);
        else
            result = head;
    }
    return result;
}

branch_t* pop_min(branch_t *head, _Bool _isbalance) // удаление узла с минимальным ключом из дерева p
{
    branch_t *result = head;
    if (head != NULL)
    {
        if(head->left == NULL)
            result = head->right;
        else
        {
            head->left = pop_min(head->left, _isbalance);
            result = head;
        }
    }
    if (_isbalance)
        result = balance_branch(result);
    return result;
}

branch_t *pop_branch_tree(branch_t *head, int pop_number, _Bool _isbalance)
{
    int rc = EXIT_SUCCESS;
    branch_t *result = head;
    if (head != NULL)
    {
        if (pop_number < head->number)
            head->left = pop_branch_tree(head->left, pop_number, _isbalance);
        else if (pop_number > head->number)
            head->right = pop_branch_tree(head->right, pop_number, _isbalance);
        else
        {
            branch_t *left = head->left;
            branch_t *right = head->right;
            head->left = NULL;
            head->right = NULL;
            free_branch(head);

            if (right == NULL)
                result = left;
            else
            {
                branch_t *min = findmin(right);
                min->right = pop_min(right, _isbalance);
                min->left = left;
                result = min;
            }
            find_all_height(result);
        }
    }
    if (_isbalance)
        result = balance_branch(result);
    return result;
}
