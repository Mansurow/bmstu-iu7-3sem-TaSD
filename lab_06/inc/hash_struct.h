#ifndef _HASH_STRUCT_H
#define _HASH_STRUCT_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#define SHIFT 2

typedef struct st_hash_elem
{
    int number;
    char _is_full;
} hash_elem_t;

typedef struct st_hash_table
{
    hash_elem_t *array;
    int size;
    int divider;
    int elements;
    int compare;
    int total_compare;
} hash_table_t;

void default_hash(hash_table_t *hash);

int hash_func(int num, int divide);
int select_prime(int max);

int push_hash(hash_table_t *hash_table, int num);
int fread_hash(FILE *f, hash_table_t *hash_table);

int pop_hash(hash_table_t *hash_table, int num);
int search_hash(hash_table_t *hash_table, int search);
hash_table_t restruct(hash_table_t table, int search, int max);

void print_hash(hash_table_t *table);

#endif