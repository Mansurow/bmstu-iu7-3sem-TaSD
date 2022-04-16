#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>
#include <stdlib.h>
#include "errors.h"

void print_menu(void);
void input_step_menu(int *step, int min, int max);
void input_top(int *top, int n);
void input_len(int *len_way);
int check_file(FILE *f);

#endif //_MENU_H
