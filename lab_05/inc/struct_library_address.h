#ifndef _STRUCT_LIBRARY_ADDRESS_H
#define _STRUCT_LIBRARY_ADDRESS_H

#include <stdio.h>
#include <stdbool.h>

#include "struct_array_queue.h"

typedef struct st_address
{
    size_t ptr;
    _Bool create;
    _Bool free;
} address_t;

typedef struct st_address_library
{
    address_t data[MAX_QUEUE];
    int size;
} address_library_t;

void default_address_library_t(address_library_t *lib);

void add_address_create(address_library_t *lib_address, size_t address);
void add_address_free(address_library_t *lib_address, size_t address);

void print_library_address(const address_library_t *lib_addresses);

#endif //_STRUCT_LIBRARY_ADDRESS_H
