#ifndef _FILL_MATRIX_H_
#define _FILL_MATRIX_H_

void default_matrix_t(matrix_t *matrix);
void default_special_matrix_t(special_matrix_t *sp_matrix);
void default_special_vector_t(special_vector_column_t *sp_vector);

void fill_matrix(int **matrix, int n, int m, int fill);

void auto_fill_matrix(matrix_t *matrix);
void auto_fill_vector_column(matrix_t *matrix);
void auto_fill(matrix_t *matrix, int non_zero_el);

#endif // _FILL_MATRIX_H_