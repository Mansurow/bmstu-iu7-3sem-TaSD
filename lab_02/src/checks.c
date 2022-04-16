#include "utils.h"
#include "checks.h"

int check_str_space (char *str)
{
    int i = 0, rc = 0;
    while (str[i] != '\0') {
        if (isspace(str[i]) != 0)
            rc = 1;
        else
        {
            rc = 0;
            break;
        }
        i++;
    }
    return rc;
}
int check_empty_data(char *str, char del)
{
    int i = 0, rc = 0, count = 0;
    while (str[i] != '\0' && rc == 0)
    {
        if (str[i] == del)
            count++;
        else
        {
            if (count > 1)
                rc = 1;
            count = 0;
        }
        i++;
    }

    return rc;
}
int check_str_without_digits(char *str)
{
    int i = 0, rc = 1;
    while (str[i] != '\0')
    {
        if ('0' <= str[i] && str[i] <= '9')
        {
            rc = 0;
            break;
        }
        i++;
    }

    return rc;
}
int check_str_tests (char *str)
{
    int rc = 0;
    if ((str[0] == '-'|| str[0] =='+') && strlen(str) == 1)
        rc = 1;
    return rc;
}
int check_name_objects(char *str)
{
    int rc = 0;
    if (strcmp(str, "История") == 0 || strcmp(str, "Культура") == 0 || strcmp(str, "Природа") == 0)
        rc = 1;
    return rc;
}
int check_is_materic(char *str)
{
    char materics [NUMBER_MATERIC][STRING_MATERIC]  = {"Европа",
                                                       "Азия",
                                                       "Северная Америка",
                                                       "Южная Америка",
                                                       "Океания",
                                                       "Африка"};
    int rc = 0, i = 0;
    i = 0;
    while (i < NUMBER_MATERIC)
    {
        if (strcmp(str, materics[i]) == 0)
        {
            rc = 1;
            break;
        }
    }
    return rc;
}
int check_str_only_digit(char *str)
{
    int i = 0, rc = 1;
    while (str[i] != '\0')
    {
        if (!('0' <= str[i] && str[i] >= '9'))
        {
            rc = 0;
            break;
        }
    }

    return rc;
}
int check_kind_sports(char *str)
{
    int rc = 0;
    if (strcmp(str, "горные лыжи") == 0 ||
        strcmp(str, "серфинг") == 0 ||
        strcmp(str, "восхождение") == 0 ||
        strcmp(str, "дайвинг") == 0)
        rc = 1;
    return rc;
}