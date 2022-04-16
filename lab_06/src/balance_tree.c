#include "../inc/tree_struct.h"

int find_branch_height(branch_t *head)
{
    if(head == NULL)
        return 0;

    int left, right;
    if (head->left != NULL)
        left = find_branch_height(head->left);
    else
        left = -1;

    if (head->right != NULL)
        right = find_branch_height(head->right);
    else
        right = -1;

    int max = left > right ? left : right;

    return max + 1;
}

void find_all_height(branch_t *head)
{
    if (head != NULL)
    {
        head->height = find_branch_height(head);
        find_all_height(head->left);
        find_all_height(head->right);
    }
}

int height(branch_t *head)
{
    return head ? head->height : -1;
}

int bfactor(branch_t *head)
{
    return head ? height(head->right) - height(head->left) : 0;
}

void fixheight(branch_t *p)
{
    if (p)
    {
        int hl = height(p->left);
        int hr = height(p->right);
        p->height = (hl > hr ? hl : hr) + 1;
    }
}

branch_t* rotateright(branch_t *right) // правый поворот вокруг p
{
    branch_t *left = right;
    if (right)
    {
        left = right->left;
        right->left = left->right;
        left->right = right;
        fixheight(right);
        fixheight(left);
    }

    return left;
}

branch_t* rotateleft(branch_t *left) // левый поворот вокруг q
{
    branch_t *right = left;
    if (left)
    {
        right = left->right;
        left->right = right->left;
        right->left = left;
        fixheight(left);
        fixheight(right);
    }
    return right;
}

branch_t* balance_branch(branch_t *head) // балансировка узла p
{
    if (head)
    {
        fixheight(head);
        if (bfactor(head) >= 2) {
            if (bfactor(head->right) < 0)
                head->right = rotateright(head->right);
            return rotateleft(head);
        }
        if (bfactor(head) <= -2) {
            if (bfactor(head->left) > 0)
                head->left = rotateleft(head->left);
            return rotateright(head);
        }
    }

    return head; // балансировка не нужна
}

branch_t *balance_tree(branch_t *head)
{
    if (head)
    {
        if (head->right)
            head->right = balance_tree(head->right);
        if (head->left)
            head->left = balance_tree(head->left);

        head = balance_branch(head);
    }
    return head;
}