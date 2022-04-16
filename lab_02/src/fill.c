#include "utils.h"
#include "errors.h"
#include "checks.h"
#include "fill.h"

void fill_key_arr_find(st_key_travel *key, size_t *n_key, st_travel *countries, size_t n_countries, char *materic, char *sport)
{
    int j = 0;
    for(int i = 0; i < n_countries; i++)
    {
        if (strcmp(countries[i].main_data.materic, materic) == 0)
            if (countries[i].tourism.tourism_sport == true &&
                strcmp(countries[i].tourism.kid_tourism.sport.kind_sport, sport) == 0)
            {
                key[j].index = i;
                strcpy(key[j].name_country, countries[i].main_data.name_country);
                j++;
            }
    }
    *n_key = j;
}
void fill_key_arr(st_key_travel *key, size_t *n_key, st_travel *countries, size_t n_countries)
{
    for(int i = 0; i < n_countries; i++)
    {
        key[i].index = i;
        strcpy(key[i].name_country, countries[i].main_data.name_country);
    }
    *n_key = n_countries;
}
int add_country(st_travel *countries, size_t *n_countries)
{
    size_t i = *n_countries;
    int rc = EXIT_SUCCESS, rc_scanf = 0;
    printf("\nВведите название страны (не должно содержать цифры): ");
    fgets(countries[i].main_data.name_country, STRING_COUNTRY + 2, stdin);
    if (strlen(countries[i].main_data.name_country) > STRING_COUNTRY)
        rc = COUNTRY_OVERFLOW;
    else
    {

        if (countries[i].main_data.name_country[strlen(countries[i].main_data.name_country) - 1] == '\n')
            countries[i].main_data.name_country[strlen(countries[i].main_data.name_country) - 1] = '\0';
        if (!check_str_without_digits(countries[i].main_data.name_country))
            rc = COUNTRY_DIGIT_ERR;
        else
        {
            //up_first_sym_and_down_other(countries[i].main_data.name_country);
            printf("Введите название столицы (не дожно содержать цифры): ");
            fgets(countries[i].main_data.capital, STRING_CAPITAL + 2, stdin);
            if (strlen(countries[i].main_data.capital) > STRING_CAPITAL)
                rc = CAPITAL_OVERFLOW;
            else
            {
                if (countries[i].main_data.capital[strlen(countries[i].main_data.capital) - 1] == '\n')
                    countries[i].main_data.capital[strlen(countries[i].main_data.capital) - 1] = '\0';
                if (!check_str_without_digits(countries[i].main_data.capital))
                    rc = COUNTRY_DIGIT_ERR;
                else
                {
                    //up_first_sym_and_down_other(countries[i].main_data.capital);
                    printf(" - Материков всего 6 и название вводятся строго по названию\n"
                           "Европа, Азия, Северная или Южная Америка, Африка, Океания\n");
                    printf("Введите материк: ");
                    fgets(countries[i].main_data.materic, STRING_MATERIC + 2, stdin);
                    if (strlen(countries[i].main_data.materic) > STRING_MATERIC)
                        rc = MATERIC_OVERFLOW;
                    else
                    {
                        if (countries[i].main_data.materic[strlen(countries[i].main_data.materic) - 1] == '\n')
                            countries[i].main_data.materic[strlen(countries[i].main_data.materic) - 1] = '\0';
                        if (!check_str_without_digits(countries[i].main_data.materic))
                            rc = MATERIC_DIGIT_ERR;
                        else
                        {
                            //up_first_sym_and_down_other(countries[i].main_data.materic);
                            printf("Введите количество жителей: ");
                            rc_scanf = scanf("%ld", &countries[i].main_data.population);
                            if (countries[i].main_data.population <= 0 || rc_scanf == 0)
                                rc = POPULATION_ZERO_ERROR;
                            else
                            {
                                long buff = 0;
                                printf("\nСтрана требует прививку/ПЦР?\n");
                                printf("<1> - Да или 0 - нет\n");
                                printf("Введите значение: ");
                                rc_scanf = scanf("%ld", &buff);
                                if (rc_scanf == 0)
                                    return EXIT_FAILURE;
                                if (buff == 0)
                                    countries[i].covid_tests = false;
                                else
                                    countries[i].covid_tests = true;

                                printf ("\nВыберите вид туризма\n"
                                        "1 - Экскурсионный\n"
                                        "2 - Пляжный\n"
                                        "3 - Спортивный\n"
                                        "Если >3 или <1 то в данных будут не заполнены (пропущены)\n"
                                        "Введите значение вида туризма: ");
                                rc_scanf = scanf("%ld", &buff);
                                if (rc_scanf == 0)
                                    return EXIT_FAILURE;

                                if (buff == 1)
                                {
                                    countries[i].tourism.tourism_sightseeing = true;
                                    printf(" - Введите количество объектов: ");
                                    rc_scanf =scanf("%ld", &buff);
                                    if (buff > 0)
                                        countries[i].tourism.kid_tourism.sightseeing.number_objects = buff;
                                    if (buff <= 0)
                                        rc = NUMBER_OBJECTS_IS_NEGATIVE;
                                    else if (rc_scanf == 0)
                                        rc = NUMBER_OBJECTS_NOT_DIGIT;
                                    else
                                    {
                                        printf(" - Введите тематику (строго одно из трех - (1)История, (2)Природа, (3)Культура): ");
                                        rc_scanf =scanf("%ld", &buff);
                                        if (buff == 1)
                                            strcpy(countries[i].tourism.kid_tourism.sightseeing.name_object, "История");
                                        else if (buff == 2)
                                            strcpy(countries[i].tourism.kid_tourism.sightseeing.name_object, "Природа");
                                        else if (buff == 3)
                                            strcpy(countries[i].tourism.kid_tourism.sightseeing.name_object, "Культура");
                                        else
                                            rc = EXIT_SUCCESS;
                                    }
                                }
                                else if (buff == 2)
                                {
                                    countries[i].tourism.tourism_beach = true;
                                    printf("\nЗначение для ввода\n"
                                           "1 - Весна\n"
                                           "2 - Лето\n"
                                           "3 - Осень\n"
                                           "4 - Зима\n"
                                           "5 - Все сезоны\n"
                                           "Другое значение - Нейзвестно\n"
                                           "Введите значение: ");
                                    scanf("%ld", &buff);
                                    if (buff > 5 || buff < 1)
                                        countries[i].tourism.kid_tourism.beach.main_season = 0;
                                    else
                                        countries[i].tourism.kid_tourism.beach.main_season = buff;
                                    printf("Введите температуру воздуха: ");
                                    rc_scanf = scanf("%hd", &countries[i].tourism.kid_tourism.beach.air_temperature);
                                    if (rc_scanf == 0)
                                        return TESTS_VALUE_ERR;
                                    printf("Введите температуру воды: ");
                                    rc_scanf = scanf("%hd", &countries[i].tourism.kid_tourism.beach.water_temperature);
                                    if (rc_scanf == 0)
                                        return TESTS_VALUE_ERR;
                                    printf("Введите время полета до страны (1 - 24 ч.): ");
                                    rc_scanf = scanf("%hu", &countries[i].tourism.kid_tourism.beach.time_flying);
                                    if (countries[i].tourism.kid_tourism.beach.time_flying <= 0 ||
                                        countries[i].tourism.kid_tourism.beach.time_flying > 24)
                                        rc = HOURS_IS_NEGATIVE;
                                    else if (rc_scanf == 0)
                                        rc = HOURS_NOT_DIGITS;
                                }
                                else if (buff == 3)
                                {
                                    countries[i].tourism.tourism_sport = true;
                                    printf("\nЗначение для ввода\n"
                                           "1 - Дайвинг\n"
                                           "2 - Серфинг\n"
                                           "3 - Горные лыжи\n"
                                           "4 - Восхождение\n");
                                    printf("Введите вид спорта: ");
                                    rc_scanf = scanf("%ld", &buff);
                                    if (buff == 1)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "дайвинг");
                                    else if (buff == 2)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "серфинг");
                                    else if (buff == 3)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "горные лыжи");
                                    else if (buff == 4)
                                        strcpy(countries[i].tourism.kid_tourism.sport.kind_sport, "восхождение");
                                    else
                                        return EXIT_FAILURE;
                                    printf("Введите стоимость: ");
                                    rc_scanf = scanf("%ld", &buff);
                                    if (buff > 0 && rc_scanf)
                                        countries[i].tourism.kid_tourism.sport.min_count_price = (long unsigned) buff;
                                    else
                                        rc = PRICE_IS_NEGATIVE;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if (rc == EXIT_SUCCESS)
        *n_countries = i + 1;
    return rc;
}