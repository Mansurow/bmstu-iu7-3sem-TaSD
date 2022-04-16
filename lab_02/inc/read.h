#ifndef _READ_H
#define _READ_H

void default_st_travel(st_travel *country);
int read_travel_country(FILE *f, st_travel *country);
int read_array_travel_country(FILE *f, st_travel *countries, size_t *n);
int my_strtok(char *del_str, char *str, char del, int *ii);
void rewrite_data(FILE *f, st_travel *countries, size_t n_countries);

#endif //_READ_H
