#ifndef _LIST_MODELLING_QUEUE_H
#define _LIST_MODELLING_QUEUE_H

#include <stdio.h>
#include <stdlib.h>

#include "struct_list_queue.h"
#include "struct_params.h"
#include "struct_modelling.h"
#include "struct_library_address.h"
#include "math_func.h"
#include "print_modelling_data.h"

void list_queue_modeling(const model_params *params, address_library_t *lib_address);

#endif //_LIST_MODELLING_QUEUE_H
