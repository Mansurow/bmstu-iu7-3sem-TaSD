#ifndef _STRUCT_PARAMS_H
#define _STRUCT_PARAMS_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#define AMOUNT_PRINT       100
#define AMOUNT_APPLICATION 1000
#define MAX_ITER  5
#define ADD_T2  6.0
#define ADD_T1  0.0
#define CONS_T2 1.0
#define CONS_T1 0.0
#define BUFF_SIZE 8

typedef struct st_params
{
    double add_t1;
    double add_t2;
    double consideration_t1;
    double consideration_t2;

    int amount_iterations;
    int amount_application;
    int amount_between_print;
} model_params;

void default_model_params(model_params *params);

void change_add_time(model_params *params);
void change_cons_time(model_params *params);

#endif //_STRUCT_PARAMS_H
