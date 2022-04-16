#ifndef _STRUCT_GRAF_H
#define _STRUCT_GRAF_H

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int top;
    int weight;
    struct node *next;
} st_list;

typedef struct {
    size_t n;
    int **matrix;
} st_matrix;

typedef struct {
    st_list **array;
    size_t n;
}st_array_list;

#endif //_STRUCT_GRAF_H
