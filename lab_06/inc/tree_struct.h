#ifndef _TREE_STRUCT_H
#define _TREE_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"

typedef struct st_tree_branch
{
    int number;
    int height;
    struct st_tree_branch *left;
    struct st_tree_branch *right;
} branch_t;

typedef struct st_tree
{
    struct st_tree_branch *head;
    int size;
    int total_compare;
} tree_t;

void default_tree(tree_t *tree);

branch_t *create_element_tree(int element);
int push_tree(branch_t **head, int number, _Bool _isbalance);
int fread_tree(FILE *f, tree_t *tree, _Bool _isbalance);

void free_branch(branch_t *head);
void free_tree(tree_t *tree);

int find_branch_height(branch_t *head);
void find_all_height(branch_t *head);
int height(branch_t *head);
int bfactor(branch_t *head);
void fixheight(branch_t *p);

branch_t* rotateright(branch_t *right);
branch_t* rotateleft(branch_t *left);
branch_t* balance_branch(branch_t *head);
branch_t *balance_tree(branch_t *head);

branch_t *findmin(branch_t *head);
branch_t* pop_min(branch_t *head, _Bool _isbalance) ;
branch_t *pop_branch_tree(branch_t *head, int pop_number, _Bool _isbalance);

int search_element(branch_t *head, int number);

void print_tree(tree_t tree);

void num_in_str(long long num, char *str);
size_t get_rank(long long num);

#endif //_TREE_STRUCT_H