#ifndef _PRINTS_H
#define _PRINTS_H

void print_task();
void print_menu();
void print_main_table();

void print_middle_str_table(char *before_str, char *str, int max_en, int max_rus);

void print_tourism_sightseeing_params(st_sightseeing *sightseeing);
void print_tourism_beach_params(st_beach *beach);
void print_tourism_sport_params(st_sport *sport);

void print_travel_country(st_travel *country);
void print_countries(st_travel *countries, size_t n);

void print_table_key(st_key_travel *key, size_t n_key);
void print_countries_on_key(st_travel *countries, st_key_travel *key, size_t n_key);
#endif //_PRINTS_H