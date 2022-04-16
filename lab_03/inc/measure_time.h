#ifndef _MEASURE_TIME_H
#define _MEASURE_TIME_H

#include <sys/time.h>
#include <inttypes.h>

#define I_STEP 100
#define STEP_PERCENT 10

size_t get_size_matrix_t(const matrix_t *matrix);
size_t get_size_sp_matrix_t(const special_matrix_t *matrix);
size_t get_size_sp_vector_t(const special_vector_column_t *vector);

void auto_measure_effinciency();

void print_measure(size_t size_m, size_t size_r, int64_t time_m, int64_t time_r, int percent);

#endif // _MEASURE_TIME_H