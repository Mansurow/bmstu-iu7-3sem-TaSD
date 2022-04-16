#ifndef _ALLOCATE_H_
#define _ALLOCATE_H_

int **allocate_matrix(int n, int m);
int allocate_special_matrix(special_matrix_t *special_matrix);
int allocate_special_vector(special_vector_column_t *special_vector);

void free_matrix(int **data, int n);
void free_special_matrix(special_matrix_t *special_matrix);
void free_special_vector(special_vector_column_t *special_vector);

#endif // _ALLOCATE_H_