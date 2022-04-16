#ifndef _TIME_H
#define _TIME_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

void make_table(void);
void make_data(int i, size_t size, size_t count_size_array, size_t one_element, int64_t time_1, int64_t time_2);
void my_cpy_st_travel(st_travel *arr_cp, st_travel *arr_src, size_t n, int repeat);
void my_cpy_st_key(st_key_travel *arr_cp, st_key_travel *arr_src, size_t n, int repeat);
void time_unsorted_arrays(st_travel *arr_с, size_t n_с, st_key_travel *arr_k, size_t n_k);

#endif //_TIME_H
