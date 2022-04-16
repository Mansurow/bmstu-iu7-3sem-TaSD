#include "utils.h"
#include "errors.h"
#include "read.h"
#include "checks.h"

void default_st_travel(st_travel *country)
{
    for (int i = 0; i < STRING_COUNTRY; i++)
        country->main_data.name_country[i] = '\0';
    for (int i = 0; i < STRING_CAPITAL; i++)
        country->main_data.capital[i] = '\0';
    for (int i = 0; i < STRING_MATERIC; i++)
        country->main_data.materic[i] = '\0';
    country->main_data.population = 0;

    country->covid_tests = false;


    country->tourism.tourism_sightseeing = false;
    country->tourism.tourism_beach = false;
    country->tourism.tourism_sport = false;

    country->tourism.kid_tourism.sightseeing.number_objects = 0;
    for (int i = 0; i < STRING_OBJECTS; i++)
        country->tourism.kid_tourism.sightseeing.name_object[i] = '\0';

    country->tourism.kid_tourism.beach.main_season = 0;
    country->tourism.kid_tourism.beach.air_temperature = 0;
    country->tourism.kid_tourism.beach.water_temperature = 0;
    country->tourism.kid_tourism.beach.time_flying = 0;

    for (int i = 0; i < STRING_SPORT; i++)
        country->tourism.kid_tourism.sport.kind_sport[i] = '\0';
    country->tourism.kid_tourism.sport.min_count_price = 0;
}
int my_strtok(char *del_str, char *str, char del, int *ii)
{
    int j = 0, i = *ii;
    while (str[i] != '\0' && str[i] != del)
    {
        del_str[j++] = str[i];
        i++;
    }
    del_str[j] = '\0';
    if (j == 0)
        return -1;
    (*ii) = str[i] == del ? i + 1: i;
    return 0;
}
int read_travel_country(FILE *f, st_travel *country)
{
    default_st_travel(country);
    char str[STRING_MAIN] = { 0 };
    int rc = EXIT_SUCCESS;

    if (fgets(str, STRING_MAIN + 2, f) == NULL)
        rc = ERR_IO;
    else if (strlen(str) > STRING_MAIN)
        rc = MAIN_STRING_OVERFLOW;
    else
    {
        if (str[strlen(str) - 1] == '\n')
            str[strlen(str) - 1] = '\0';
        if (check_empty_data(str, ';'))
            rc = DATA_EMPTY_ERR;
        else
        {
            char *del = ";";
            char *data = NULL;
            char *er_digit = NULL;

            data = strtok(str, del);
            if (data == NULL)
                rc = DATA_EMPTY_ERR;
            else
                for(int st_dt = 1; data != NULL && rc == EXIT_SUCCESS; st_dt++)
                {
                    if (check_str_space(data))
                        rc = DATA_EMPTY_ERR;
                    else
                    {
                        if (st_dt == 1)
                        {
                            if (strlen(data) > STRING_COUNTRY)
                                rc = COUNTRY_OVERFLOW;
                            else
                            {
                                if (check_str_without_digits(data))
                                    strcpy(country->main_data.name_country, data);
                                else
                                    rc = COUNTRY_DIGIT_ERR;
                            }
                        }
                        else if (st_dt == 2)
                        {
                            if (strlen(data) > STRING_CAPITAL)
                                rc = CAPITAL_OVERFLOW;
                            else
                            {
                                if (check_str_without_digits(data))
                                    strcpy(country->main_data.capital, data);
                                else
                                    rc = CAPITAL_DIGIT_ERR;
                            }
                        }
                        else if (st_dt == 3)
                        {
                            if (strlen(data) > STRING_MATERIC)
                                rc = MATERIC_OVERFLOW;
                            else
                            {
                                if (check_str_without_digits(data))
                                    strcpy(country->main_data.materic, data);
                                else
                                    rc = MATERIC_DIGIT_ERR;
                            }
                        }
                        else if (st_dt == 4)
                        {
                            country->main_data.population = strtol(data, &er_digit, 10);
                            if (strlen(er_digit) > 0)
                                rc = POPULATION_NOT_DIGIT;
                            else if (country->main_data.population <= 0)
                                rc = POPULATION_ZERO_ERROR;
                        }
                        else if (st_dt == 5)
                        {
                            if (!check_str_tests(data))
                                rc = TESTS_VALUE_ERR;
                            else
                            {
                                if (data[0] == '-')
                                    country->covid_tests = 0;
                                else if (data[0] == '+')
                                    country->covid_tests = 1;
                            }
                        }
                        else if (st_dt == 6)
                        {
                            char kid_tourism[STRING_MATERIC] = { 0 };
                            int erdel = 0;
                            for (int i = 0; data[i] != '\0';)
                            {
                                unsigned short kid_dt = 1;
                                erdel = my_strtok(kid_tourism, data, ':', &i);
                                if (erdel != 0)
                                    rc = KIND_TOURISM_EMPTY;
                                else
                                {
                                    if (strcmp("-", data) == 0)
                                    {
                                        country->tourism.tourism_sightseeing = false;
                                        country->tourism.tourism_beach = false;
                                        country->tourism.tourism_sport = false;
                                    }
                                    else if (strcmp("Экскурсионный", kid_tourism) == 0)
                                    {
                                        country->tourism.tourism_sightseeing = 1;
                                        erdel = my_strtok(kid_tourism, data, ',', &i);
                                        while (erdel == 0)
                                        {
                                            int buff;
                                            if (kid_dt == 1)
                                            {
                                                buff = strtol(kid_tourism, &er_digit, 10);
                                                if (strlen(er_digit) > 0)
                                                    rc = NUMBER_OBJECTS_NOT_DIGIT;
                                                else if (buff < 0)
                                                    rc = NUMBER_OBJECTS_IS_NEGATIVE;
                                                else
                                                    country->tourism.kid_tourism.sightseeing.number_objects= buff;
                                            }
                                            else if (kid_dt == 2)
                                            {
                                                if (strlen(kid_tourism) > STRING_OBJECTS)
                                                    rc = OBJECTS_OVERFLOW;
                                                else if (!check_name_objects(kid_tourism))
                                                    rc = NAME_OBJECTS_IS_WRONG;
                                                else
                                                    strcpy(country->tourism.kid_tourism.sightseeing.name_object, kid_tourism);
                                            }
                                            else
                                                rc = KIND_PARAMS_MORE;
                                            erdel = my_strtok(kid_tourism, data, ',', &i);
                                            kid_dt++;
                                        }
                                    }
                                    else if (strcmp("Пляжный", kid_tourism) == 0)
                                    {
                                        country->tourism.tourism_beach = true;
                                        erdel = my_strtok(kid_tourism, data, ',', &i);
                                        while (erdel == 0)
                                        {
                                            if (kid_dt == 1)
                                            {
                                                int buff;
                                                buff = strtol(kid_tourism, &er_digit, 10);
                                                if (strlen(er_digit) > 0)
                                                    rc = SEASON_NOT_DIGIT;
                                                else if (buff < 0)
                                                    rc = SEASON_IS_NEGATIVE;
                                                else
                                                    country->tourism.kid_tourism.beach.main_season = (unsigned short) buff;
                                            }
                                            else if (kid_dt == 2)
                                            {
                                                country->tourism.kid_tourism.beach.air_temperature = (short) strtol(kid_tourism, &er_digit, 10);
                                                if (strlen(er_digit) > 0)
                                                    rc = TEMP_NOT_DIGIT;
                                            }
                                            else if (kid_dt == 3)
                                            {
                                                country->tourism.kid_tourism.beach.water_temperature = (short) strtol(kid_tourism, &er_digit, 10);
                                                if (strlen(er_digit) > 0)
                                                    rc = TEMP_NOT_DIGIT;
                                            } else if (kid_dt == 4)
                                            {
                                                int buff;
                                                buff = strtol(kid_tourism, &er_digit, 10);
                                                if (strlen(er_digit) > 0)
                                                    rc = HOURS_NOT_DIGITS;
                                                else if (buff < 1 || buff > 24)
                                                    rc = HOURS_IS_NEGATIVE;
                                                else
                                                    country->tourism.kid_tourism.beach.time_flying = (unsigned short) buff;
                                            } else
                                                rc = KIND_PARAMS_MORE;
                                            erdel = my_strtok(kid_tourism, data, ',', &i);
                                            kid_dt++;
                                        }
                                    }
                                    else if (strcmp("Спортивный", kid_tourism) == 0)
                                    {
                                        country->tourism.tourism_sport = true;
                                        erdel = my_strtok(kid_tourism, data, ',', &i);
                                        while (erdel == 0 && rc == 0)
                                        {
                                            if (kid_dt == 1)
                                            {
                                                if (!check_str_without_digits(kid_tourism))
                                                    rc = KIND_SPORT_ERR;
                                                else if (!check_kind_sports(kid_tourism))
                                                    rc = KIND_TOURISM_NOT;
                                                else
                                                  strcpy(country->tourism.kid_tourism.sport.kind_sport, kid_tourism);
                                            }
                                            else if (kid_dt == 2)
                                            {
                                                int buff = strtol(kid_tourism, &er_digit, 10);
                                                if (strlen(er_digit) > 0)
                                                    rc = PRICE_NOT_DIGIT;
                                                else if (buff < 0)
                                                    rc = PRICE_IS_NEGATIVE;
                                                else
                                                    country->tourism.kid_tourism.sport.min_count_price = buff;
                                            } else
                                                rc = KIND_PARAMS_MORE;
                                            erdel = my_strtok(kid_tourism, data, ',', &i);
                                            kid_dt++;
                                        }
                                    }
                                    else
                                        rc = KIND_TOURISM_ERR;
                                }

                            }
                        }
//
//                        else if (st_dt == 8)
//                        {
//                            int buff = strtol(data, &er_digit, 10);
//                            if (strlen(er_digit) > 0)
//                                rc = PRICE_NOT_DIGIT;
//                            else if (buff < 0)
//                                rc = PRICE_IS_NEGATIVE;
//                            else
//                                country->tourism.min_count_price = buff;
//                        }
                        data = strtok(NULL, del);
                    }
                }
        }
    }
    return rc;
}
int read_array_travel_country(FILE *f, st_travel *countries, size_t *n)
{
    int i = 0, rc = EXIT_SUCCESS;
    st_travel cur;
    while (rc == EXIT_SUCCESS)
    {
        rc = read_travel_country(f, &cur);
        if (rc == EXIT_SUCCESS)
        {
            if (i <= NUMBER_COUNTRY)
                countries[i++] = cur;
            else
                rc = ARRAY_OVERFLOW;
        }
    }
    if (rc == ERR_IO)
        rc = EXIT_SUCCESS;
    if (i <= 0)
        rc = FILE_IS_EMPTY;
    *n = i;
    return rc;
}
void rewrite_data(FILE *f, st_travel *countries, size_t n_countries)
{
    for (int i = 0; i < n_countries; i++)
    {
        fprintf(f, "%s;%s;%s;%ld;", countries[i].main_data.name_country,
                countries[i].main_data.capital,
                countries[i].main_data.materic,
                countries[i].main_data.population);
        if (countries[i].covid_tests == true)
            fprintf(f, "+;");
        else
            fprintf(f, "-;");

        if (countries[i].tourism.tourism_sightseeing == false &&
            countries[i].tourism.tourism_beach == false &&
            countries[i].tourism.tourism_sport == false)
            fprintf(f, "-;");
        else
        {
            if (countries[i].tourism.tourism_sightseeing == true)
                fprintf(f, "Экскурсионный:%u,%s\n", countries[i].tourism.kid_tourism.sightseeing.number_objects,
                                                  countries[i].tourism.kid_tourism.sightseeing.name_object);
            else if (countries[i].tourism.tourism_beach == true)
                fprintf(f, "Пляжный:%hd,%hd,%hd,%hd\n", countries[i].tourism.kid_tourism.beach.main_season,
                        countries[i].tourism.kid_tourism.beach.air_temperature,
                        countries[i].tourism.kid_tourism.beach.water_temperature,
                        countries[i].tourism.kid_tourism.beach.time_flying);
            else if (countries[i].tourism.tourism_sport == true) {
                fprintf(f, "Спортивный:%s,%ld\n", countries[i].tourism.kid_tourism.sport.kind_sport,
                                               countries[i].tourism.kid_tourism.sport.min_count_price);
            }
        }
    }
}