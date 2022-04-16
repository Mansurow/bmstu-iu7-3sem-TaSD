#include "../inc/struct_array_queue.h"

void default_array_queue(array_queue_t *queue)
{
    for (int i = 0; i < MAX_QUEUE; i++)
        queue->data[i] = 0;
    queue->size = 0;
    queue->head = queue->data; // Pout
    queue->tail = queue->data; // Pin
}

int array_push_application(array_queue_t *queue, int element)
{
    int rc = EXIT_SUCCESS;
    if (queue->size >= MAX_QUEUE)
        rc = ARRAY_OVERFLOW;
    else
    {
        if (queue->tail >= queue->data + MAX_QUEUE)
            queue->tail = queue->data;
        *(queue->tail) = element;
        queue->tail++;
        queue->size++;
    }

    return rc;
}

int array_pop_application(array_queue_t *queue)
{
    int rc = EXIT_SUCCESS;
    if (queue->head == queue->tail && queue->size == 0)
        rc = ARRAY_EMPTY;
    else
    {
        if (queue->head >= queue->data + MAX_QUEUE)
            queue->head = queue->data;
        queue->head++;
        queue->size--;
    }

    return rc;
}

void print_array_application(const array_queue_t *queue)
{
    if (queue->size > 0)
    {
        if (queue->tail > queue->head)
            for (int *i = queue->head; i < queue->tail; i++)
                printf("%d ", *i);
        else
        {
            for (int *i = queue->head; i < queue->data + MAX_QUEUE; i++)
                printf("%d ", *i);
            for (int *i = (int *) queue->data; i < queue->tail; i++)
                printf("%d ", *i);
        }
        printf("\n");
    }
    else
        printf("Пустая очередь!\n");
}
