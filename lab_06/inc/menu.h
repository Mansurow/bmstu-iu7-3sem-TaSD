#ifndef _MENU_H
#define _MENU_H

#include <stdio.h>
#include <stdlib.h>

#include "errors.h"

#define BUFF_SIZE 8

void print_menu(void);
void input_step_menu(int *step, int min, int max);
void input_number(int *number);
int check_file(FILE *f);

#endif //_MENU_H
