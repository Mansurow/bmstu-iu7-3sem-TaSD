#ifndef _SORTS_H
#define _SORTS_H

void buble_sort_key(st_key_travel *key, size_t n_key);
void buble_sort_table(st_travel *countries, size_t n_countries);
void buble_sort_flag_key(st_key_travel *key, size_t n_key);
void buble_sort_flag_table(st_travel *countries, size_t n_countries);
void insert_sort_table(st_travel *countries, size_t n_countries);
void insert_sort_key(st_key_travel *key, size_t n_key);
void insert_sort_binary_table(st_travel *countries, size_t n_countries);
void insert_sort_binary_key(st_key_travel *key, size_t n_key);
void shell_sort_table(st_travel *countries, size_t n_countries);
void shell_sort_key(st_key_travel *key, size_t n_key);
void qiuck_sort_table(st_travel *countries, size_t left, size_t right);
void qiuck_sort_key(st_key_travel *key, size_t left, size_t right);

#endif //T_SORTS_H
