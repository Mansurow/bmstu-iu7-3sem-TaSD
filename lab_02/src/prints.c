#include "utils.h"
#include "prints.h"

void print_main_table()
{
    printf("+------------------------------+--------------------+------------------+----------------+------------+------------------------------------+\n");
    printf("|%12s%6s%12s|%6s%7s%7s|%5s%7s%6s| %s | %s |%13s%11s%12s|\n",
           "", "Страна", "",
           "", "Столица", "",
           "", "Материк", "",
           "Кол-во жителей",
           "Вакцинация",
           "", "Вид туризма", "");
    printf("+------------------------------+--------------------+------------------+----------------+------------+------------------------------------+\n");
//    printf("|%30s|%20s|%18s|%16s|%12s|%10s|%34s+%14s|%23s|\n", "", "", "", "", "", "", "", "", "");
}
void print_countries_on_key(st_travel *countries, st_key_travel *key, size_t n_key)
{
    print_main_table();
    for (size_t i = 0; i < n_key; i++)
        print_travel_country(&countries[key[i].index]);
}
void print_middle_str_table(char *before_str, char *str, int max_en, int max_rus)
{
    int len = strlen(str);
    if (('A' <= str[0] && str[0] <= 'Z') ||
        ('a' <= str[0] && str[0] <= 'z'))
    {
        int len_d =  (max_en - len) / 2;
        int len_m =  (max_en - len) % 2;
        char spaces[STRING_COUNTRY / 4] = { 0 };
        for (int i = 0; i < len_d; i++)
            spaces[i] = ' ';
        if (len == max_en)
            printf("%s%s",before_str, str);
        else if (len_m == 0)
            printf("%s%s%s%s",before_str, spaces, str, spaces);
        else if (len_m != 0)
        {
            if (len_d == 0)
                printf("%s %s", before_str, str);
            else
                printf("%s%s%s %s", before_str, spaces, str, spaces);
        }
    } else if (-48 == str[0])
    {
        int len_d =  (max_rus - len) / 4;
        int len_m =  (max_rus - len) % 4;
        char spaces[STRING_COUNTRY / 2] = { 0 };
        for (int i = 0; i < len_d; i++)
            spaces[i] = ' ';
        if (len == max_rus)
            printf("%s%s",before_str, str);
        else if (len_m == 0)
            printf("%s%s%s%s",before_str, spaces, str, spaces);
        else if (len_m != 0)
        {
            if (len_d == 0)
                printf("%s %s", before_str, str);
            else
                printf("%s%s%s %s", before_str, spaces, str, spaces);
        }
    }
}
void print_tourism_sightseeing_params(st_sightseeing *sightseeing)
{
    printf("|%30s|%20s|%18s|%16s|%12s|%s%7d%10s|\n", "", "", "", "", "",
               "    - Кол-во дост.:",
               sightseeing->number_objects, "");
    printf("|%30s|%20s|%18s|%16s|%12s|%s%8s%13s|\n", "", "", "", "", "",
               "    - Тематика: ",
               sightseeing->name_object, "");
}
void print_tourism_beach_params(st_beach *beach)
{
    if (beach->main_season >= 0)
        switch (beach->main_season)
        {
            case 0:
                printf("|%30s|%20s|%18s|%16s|%12s|%s%4s|\n", "", "", "", "", "", "    - Основной сезон: Неизвестен", "");
                break;
            case 1:
                printf("|%30s|%20s|%18s|%16s|%12s|%s%9s|\n", "", "", "", "", "", "    - Основной сезон: Весна", "");
                break;
            case 2:
                printf("|%30s|%20s|%18s|%16s|%12s|%s%10s|\n", "", "", "", "", "", "    - Основной сезон: Лето", "");
                break;
            case 3:
                printf("|%30s|%20s|%18s|%16s|%12s|%s%10s|\n", "", "", "", "", "", "    - Основной сезон: Зима", "");
                break;
            case 4:
                printf("|%30s|%20s|%18s|%16s|%12s|%s%10s|\n", "", "", "", "", "", "    - Основной сезон: Осень", "");
                break;
            case 5:
                printf("|%30s|%20s|%18s|%16s|%12s|%s%11s|\n", "", "", "", "", "", "    - Основной сезон: Все", "");
                break;
        }
    printf("|%30s|%20s|%18s|%16s|%12s|%s%3d%13s|\n", "", "", "", "", "",
           "    - Темп. воздуха:",
           beach->air_temperature, "");
    printf("|%30s|%20s|%18s|%16s|%12s|%s%3d%16s|\n", "", "", "", "", "",
           "    - Темп. воды:",
           beach->water_temperature, "");
    printf("|%30s|%20s|%18s|%16s|%12s|%s%3d%14s|\n", "", "", "", "", "",
           "    - Время полета:",
           beach->time_flying, "");
}
void print_tourism_sport_params(st_sport *sport)
{
    int space = 18 - strlen(sport->kind_sport) / 2;
    for (int i = 0; sport->kind_sport[i] != '\0'; i++)
        if (sport->kind_sport[i] > 0)
            space--;
    printf("|%30s|%20s|%18s|%16s|%12s|%s%13s", "", "", "", "", "",
           "    - Вид спорта: ",
           sport->kind_sport);
    for (int i = 0; i < space; i++)
        printf(" ");
    printf("|\n");
    printf("|%30s|%20s|%18s|%16s|%12s|%s%8ld%11s|\n", "", "", "", "", "",
           "    - Стоимость: ",
           sport->min_count_price, "");
}
void print_travel_country(st_travel *country) {
    // строка первая
    print_middle_str_table("|", country->main_data.name_country, 30, 60);
    print_middle_str_table("|", country->main_data.capital, 20, 40);
    print_middle_str_table("|", country->main_data.materic, 18, 36);
    printf("|%13ld   ", country->main_data.population);
    if (country->covid_tests == false)
        printf("|  %s  ", "Не нужны");
    else
        printf("|   %s    ", "Нужны");

    if (country->tourism.tourism_sightseeing == true)
        printf("| %s%21s|\n", "Экскурсионный:", "");
    else if (country->tourism.tourism_beach == true)
        printf("| %s%27s|\n", "Пляжный:", "");
    else if (country->tourism.tourism_sport == true)
        printf("| %s%24s|\n", "Спортивный:", "");
    else
        printf("|%13s%s%13s|\n", "", "Неизвестно", "");

    if (country->tourism.tourism_sightseeing == true)
    {
        print_tourism_sightseeing_params(&country->tourism.kid_tourism.sightseeing);
        if (country->tourism.tourism_beach == true)
        {
            printf("|%30s|%20s|%18s|%16s|%12s|%10s|%s%27s|\n", "", "", "", "", "", "",
                   " Пляжный:", "");
            print_tourism_beach_params(&country->tourism.kid_tourism.beach);
        }
        if (country->tourism.tourism_sport == true)
        {
            printf("|%30s|%20s|%18s|%16s|%12s|%10s|%s%24s|\n", "", "", "", "", "", "",
                   " Спортивный:", "");
            print_tourism_sport_params(&country->tourism.kid_tourism.sport);
        }
    }
    else if (country->tourism.tourism_beach == true)
    {
        print_tourism_beach_params(&country->tourism.kid_tourism.beach);
        if (country->tourism.tourism_sport == true)
        {
            printf("|%30s|%20s|%18s|%16s|%12s|%10s|%s%24s|\\n", "", "", "", "", "", "",
                   " Спортивный:", "");
            print_tourism_sport_params(&country->tourism.kid_tourism.sport);
        }
    } else if (country->tourism.tourism_sport == true)
        print_tourism_sport_params(&country->tourism.kid_tourism.sport);
    printf("+");
    for (int i = 0; i < 137; i++)
        printf("-");
    printf("+\n");
}
void print_countries(st_travel *countries, size_t n)
{
    print_main_table();
    for (int i = 0; i < n; i++)
        print_travel_country(&countries[i]);
}
void print_table_key(st_key_travel *key, size_t n_key)
{
    printf("Таблица по ключу:\n");
    printf("+--------+------------------------------+\n");
    printf("| %s |%12s%6s%12s|\n", "Индекс", "", "Страна", "");
    printf("+--------+------------------------------+\n");
    for (size_t i = 0; i < n_key; i++)
    {
        printf("|%5d%3s", key[i].index, "");
        print_middle_str_table("|", key[i].name_country, 30, 60);
        printf("|\n");
        printf("+--------+------------------------------+\n");
    }
    printf("\n");
}

void print_menu()
{
    printf("----------MENU---------                ---------------Описание--------------\n"
           "1 - Вывести все страны.                При добавление стран есть ряд ограничений:\n"
           "2 - Добавить страну.                    - Название стран небольше 30 символов\n"
           "3 - Удалить страну.                     - Название столиц небольше 20 символов\n"
           "4 - Найти страны (указав материк        - Название материков(только Европа,\n"
           "                 и вид спорта)              Северная или Южная Америка, Азия,\n"
           "5 - Отсортировать все страны.               Океания) ввод должен соотвествовать.\n"
           "6 - Отсортировать все страны(по ключу).  - Название типов туризма только 3 вида\n"
           "7 - Оценка Эффетивности                    Экскурсионный,Пляжный,Спортивный\n"
           "                                        - Название для ввидов спортивного туризма\n"
           "                                             небольше 40 элементов\n");
}
void print_task()
{
    printf("-------------------Задание 2 ТиСД--------------------------\n"
           "Ввести список стран, в которых можно отдохнуть, содержащий\n"
           "название страны, количество жителей, столицу, материк,\n"
           "нужна ли прививка или ПЦР, основной вид туризма\n"
           "(экскурсионный - количество объектов, основной вид (природа,\n"
           "история, искусство); пляжный – основной сезон, температура\n"
           "воздуха и воды, время полета до страны; спортивный – вид\n"
           "спорта (горные лыжи, серфинг, восхождения), минимальная\n"
           "стоимость отдыха,). Вывести список стран на выбранном\n"
           "материке, где можно заняться указанным видом спорта.\n\n");
}