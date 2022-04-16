#ifndef _TAKE_MEASURE_H
#define _TAKE_MEASURE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <inttypes.h>

#include "struct_array_queue.h"
#include "struct_list_queue.h"

#define STEP_M 100
#define STEP 10
#define I_S  100
#define MAX_MEASURE 1000

size_t get_size_array();
size_t get_size_list(size_t n);

void print_main_table_size();
void print_table_size(size_t count, size_t array, size_t list);

void print_main_table_time();
void print_table_time(size_t count, int64_t time_push_array, int64_t time_pop_array, int64_t time_push_list, int64_t time_pop_list);

void analys_size_queue();
void analys_time_queue();

#endif //_TAKE_MEASURE_H
