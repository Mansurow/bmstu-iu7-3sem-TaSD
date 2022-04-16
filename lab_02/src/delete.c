#include "utils.h"
#include "delete.h"

int delete_country_on_name(st_travel *countries, size_t *n_countries, char *del_country)
{
    int rc_del = 0;
    if (*n_countries == 0)
        rc_del = -1;
    else
        for (size_t i = 0; i < *n_countries; i++)
            if (strcmp(countries[i].main_data.name_country, del_country) == 0)
            {
                for (size_t j = i; j < *n_countries - 1; j++)
                    countries[j] = countries[j + 1];
                (*n_countries)--;
                rc_del = 1;
            }
    return rc_del;
}