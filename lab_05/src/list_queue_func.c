#include "../inc/struct_list_queue.h"

void default_list_queue(list_queue_t *queue)
{
    queue->head = NULL;
    queue->size = 0;
}

node_queue_t *symbol_create(int el)
{
    node_queue_t *node= malloc(sizeof(node_queue_t));
    if (node != NULL)
    {
        node->data = el;
        node->next = NULL;
    }

    return node;
}

int list_push_application(list_queue_t *queue, int element)
{
    int rc = EXIT_SUCCESS;
    node_queue_t *node = symbol_create(element);
    if (node != NULL)
    {
        node_queue_t *tail = queue->head;
        //if (tail != NULL)
        //    for (; tail->next; tail = tail->next);
        for (int i = 0; i < queue->size - 1; i++)
            tail = tail->next;
        if (queue->head == NULL)
            queue->head = node;
        else
            tail->next = node;
        tail = node;
        queue->size++;
        // в начало
        //node->next = *queue;
        //*queue = node;
    }
    else
        rc = MEMORY_ERROR;

    return rc;
}

int list_pop_application(list_queue_t *queue)
{
    int rc = EXIT_SUCCESS;
    if (queue->head == NULL)
        rc = LIST_EMPTY;
    else
    {
        if (queue->size == 1)
        {
            free(queue->head);
            queue->head = NULL;
        }
        else
        {
            node_queue_t *head = queue->head;
            queue->head = queue->head->next;
            free(head);
        }
        queue->size--;
    }

    return rc;
}

void print_list_application(list_queue_t queue)
{
    if (queue.head == NULL)
        printf("Пустая очередь!\n");
    else
    {
        for (; queue.head; queue.head = queue.head->next)
            printf("%d ",  queue.head->data);
        printf("\n");
    }
}

void free_list_application(list_queue_t *queue)
{
    if (queue->head != NULL)
    {
        node_queue_t *head;
        for (; queue->head; queue->head = head)
        {
            head = queue->head->next;
            free(queue->head);
        }
        head = NULL;
        queue->head = NULL;
    }
}
