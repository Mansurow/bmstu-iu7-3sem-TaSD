#ifndef _PRINT_GRAF_H
#define _PRINT_GRAF_H

#include "struct_graf.h"

void print_graphviz_matrix(FILE *graph_visual, st_matrix *matrix) ;
void print_matrix(const st_matrix *graf);

void print_graphviz_list(FILE *graph_visual, const st_array_list *graf);
void print_array_list(const st_array_list *graf);

#endif //_PRINT_GRAF_H
