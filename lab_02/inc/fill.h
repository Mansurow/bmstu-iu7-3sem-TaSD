#ifndef _FILL_H
#define _FILL_H

void fill_key_arr_find(st_key_travel *key, size_t *n_key, st_travel *countries, size_t n_countries, char *materic, char *sport);
void fill_key_arr(st_key_travel *key, size_t *n_key, st_travel *countries, size_t n_countries);
int add_country(st_travel *countries, size_t *n_countries);

#endif //_FILL_H
