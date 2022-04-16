#ifndef _MEMORY_GRAF_H
#define _MEMORY_GRAF_H

#include "struct_graf.h"
#include "errors.h"

void default_matrix_graf(st_matrix *graf);
void default_list_graf(st_array_list *graf);

void free_matrix(int ***matrix, size_t n);
int **allocate_matrix(size_t n, size_t m);

st_list **alocate_array_list(size_t n);
st_list *top_create(int top, int weight);
int list_push(st_list **head, int top, int weight);
void free_list(st_list **head);
void free_array_list(st_array_list *graf);

#endif //_MEMORY_GRAF_H
