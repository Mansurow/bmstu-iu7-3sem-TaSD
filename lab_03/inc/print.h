#ifndef _PRINT_H_
#define _PRINT_H

void print_main_menu();
void print_matrix_menu();
void print_vector_menu();

void print_usual_matrix(const matrix_t *matrix);
void print_special_matrix(const special_matrix_t *matrix);
void print_special_vector(const special_vector_column_t *matrix);

void print_err_matrix(int rc);
#endif // _PRINT_H_