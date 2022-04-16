#include "../inc/tree_struct.h"

int search_element(branch_t *head, int number)
{
    int result = 0;
    if (head != NULL)
    {
        for (; head && result <= 0;)
        {
            result--;
            if (number > head->number)
                head = head->right;
            else if (number < head->number)
                head = head->left;
            else
                result = 0 - result;
        }
    }

    return result;
}
