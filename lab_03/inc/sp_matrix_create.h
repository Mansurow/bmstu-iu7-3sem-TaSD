#ifndef _SP_MATRIX_CREATE_
#define _SP_MATRIX_CREATE_

int get_zero_element(int **matrix, int n, int m);
int create_special_matrix(special_matrix_t *special_matrix, const matrix_t *matrix);
int create_special_vector(special_vector_column_t *special_vector, const matrix_t *matrix);

int create_usual_matrix(int ***matrix, int n, int m);

#endif // _SP_MATRIX_CREATE_