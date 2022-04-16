#ifndef _STRUCT_ARRAY_QUEUE_H
#define _STRUCT_ARRAY_QUEUE_H

#define MAX_QUEUE 1000

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

typedef struct st_array_queue
{
    int data[MAX_QUEUE];
    int size;
    int *head;
    int *tail;
} array_queue_t;

void default_array_queue(array_queue_t *queue);

int array_push_application(array_queue_t *queue, int element);
int array_pop_application(array_queue_t *queue);
void print_array_application(const array_queue_t *queue);

#endif //_STRUCT_ARRAY_QUEUE_H
