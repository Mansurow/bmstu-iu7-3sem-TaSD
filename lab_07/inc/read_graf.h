#ifndef _READ_GRAF_H
#define _READ_GRAF_H

#include <ctype.h>

#define BUFF_SIZE 8

#include "struct_graf.h"
#include "memory_graf.h"
#include "errors.h"

int get_row(FILE *f, size_t *row);
int get_column(FILE *f, size_t *column);

int read_file_matrix(FILE *f, st_matrix *graf);
int read_file_list(FILE *f, st_array_list *graf);

#endif //_READ_GRAF_H
