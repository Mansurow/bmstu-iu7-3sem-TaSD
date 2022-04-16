#include "../inc/tree_struct.h"

branch_t *create_element_tree(int element)
{
    branch_t *head = NULL;

    head = malloc(sizeof(branch_t));
    if (head)
    {
        head->left = NULL;
        head->right = NULL;
        head->height = 0;
        head->number = element;
    }

    return head;
}

void free_branch(branch_t *head)
{
    if (head != NULL)
    {
        free_branch(head->right);
        free_branch(head->left);
    }
    free(head);
}

void free_tree(tree_t *tree)
{
    free_branch(tree->head);
    tree->head = NULL;
}
