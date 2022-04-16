#ifndef _STRUCT_ARRAY_LIST_H
#define _STRUCT_ARRAY_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

typedef struct st_node_queue
{
    int data;
    struct st_node_queue *next;
} node_queue_t;

typedef struct st_list_queue
{
    node_queue_t *head;
    int size;
} list_queue_t;

void default_list_queue(list_queue_t *queue);

int list_push_application(list_queue_t *queue, int element);
int list_pop_application(list_queue_t *queue);
void print_list_application(list_queue_t queue);
void free_list_application(list_queue_t *queue);

#endif //_STRUCT_ARRAY_LIST_H
