#ifndef _FIND_TOP_H
#define _FIND_TOP_H

#include "struct_graf.h"
#include "errors.h"

int algoritm_ballman_fold_matrix(const st_matrix *graf, int start_top, int *distance);
int algoritm_dijkstra_matrix(const st_matrix *graf, int start_top, int *distance);

int algoritm_ballman_fold_list(const st_array_list *graf, int start_top, int *distance);
int algoritm_dijkstra_list(const st_array_list *graf, int start_top, int *distance);

void print_top_as_input(int *distance, int size, int max_way, int start_top);

#endif //_FIND_TOP_H
