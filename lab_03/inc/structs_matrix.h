#ifndef _STRUCTS_MATRIX_H_
#define _STRUCTS_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

#define MIN_N 1
#define MAX_N 5000
#define MIN_M MIN_N
#define MAX_M MAX_N
#define MAX_PRINT 30
#define MAX_NUMBER 200

typedef struct st_usual_matrix
{
    int **matrix;
    int n;
    int m;
} matrix_t;
typedef struct st_list
{
    int *list;
} list_t;
typedef struct st_special_matrix
{
    int n;
    int m;
    int na;

    int *A;
    int *JA;
    list_t IA;
} special_matrix_t;
typedef struct st_special_vector
{
    int n;
    int na;

    int *A;
    list_t IA;
} special_vector_column_t ;

#endif // _STRUCTS_MATRIX_H_