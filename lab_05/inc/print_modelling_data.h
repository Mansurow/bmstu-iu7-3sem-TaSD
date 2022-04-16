#ifndef _PRINT_MODELLING_DATA_H
#define _PRINT_MODELLING_DATA_H

#include <stdio.h>
#include <math.h>
#include "struct_modelling.h"
#include "struct_params.h"

void default_modeling_t(modeling_t *modeling);

void print_model_data_between(const modeling_t *modeling, const model_params *params);
void print_model_data(const modeling_t *modeling, const model_params *params);

#endif //_PRINT_MODELLING_DATA_H
