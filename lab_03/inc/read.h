#ifndef _READ_H_
#define _READ_H_

int input_step_menu(int *step, int min, int max);

int read_matrix_size(int *n, int *m);
int read_size_vector_column(int *n);
int read_auto_percent(int *percent);

int read_usual_matrix_element(int **matrix, int n, int m);

int read_non_zero_elements(int *count, int n, int m);
void read_special_matrix_element(int **matrix, int n, int m, int non_zero_el);
void read_special_vector_column_element(int **matrix, int n, int non_zero_el);

int read_usual_matrix_t (matrix_t *matrix);
int read_special_matrix_t(matrix_t *matrix);

int read_usual_vector_column(matrix_t *matrix);
int read_special_vector_column(matrix_t *matrix);

#endif // _READ_H_