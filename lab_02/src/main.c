#include "utils.h"
#include "errors.h"
#include "read.h"
#include "checks.h"
#include "sorts.h"
#include "fill.h"
#include "delete.h"
#include "prints.h"
#include "time.h"

void print_add_err(int rc)
{
    switch (rc)
    {
        case EXIT_FAILURE:
            printf("\nОшибка: Введенно неправильное значение.");
            break;
        case COUNTRY_DIGIT_ERR:
            printf("\nОшибка: В названии страны есть цифры.");
            break;
        case CAPITAL_DIGIT_ERR:
            printf("\nОшибка: В названии столицы есть цифры.");
            break;
        case MATERIC_DIGIT_ERR:
            printf("\nОшибка: В названии материка есть цифры.");
            break;
        case COUNTRY_OVERFLOW:
            printf("\nОшибка: Строка для ввода страны переполнена.");
            break;
        case CAPITAL_OVERFLOW:
            printf("\nОшибка: Строка для ввода столицы переполнена.");
            break;
        case MATERIC_OVERFLOW:
            printf("\nОшибка: Строка для ввода материка переполнена.");
            break;
        case NOT_IS_MATERIC:
            printf("\nОшибка: Это не материк.");
            break;
        case POPULATION_ZERO_ERROR:
            printf("\nОшибка: Популяция население не может быть отрицательным или нулевым.");
            break;
        case NUMBER_OBJECTS_IS_NEGATIVE:
            printf("\nОшибка: Кол-во объектов не может быть отрицательным или равняться нулю.");
            break;
        case NUMBER_OBJECTS_NOT_DIGIT:
            printf("\nОшибка: Кол-во оюъектов только может быть числом.");
            break;
        case KIND_PARAMS_MORE:
            printf("\nОшибка: Для количетва туризма введдено больше значений, чем ожидалось.");
            break;
        case KIND_TOURISM_EMPTY:
            printf("\nОшибка: Вид туризма пуст для прoпущен необходимо ;-;");
            break;
        case PRICE_IS_NEGATIVE:
            printf("\nОшибка: Общая стоимость не может быть негативным или нулевым");
            break;
        case PRICE_NOT_DIGIT:
            printf("\nОшибка: Общая стоимость не число");
            break;
        case TESTS_VALUE_ERR:
            printf("\nОшибка: Данные о пцр или вакцинации не могут быть символами ;-; или ;+;");
            break;
        case DATA_EMPTY_ERR:
            printf("\nОшибка: Пропущено значение или записано - ;;");
            break;
        case FILE_NOT_FOUND:
            printf("\nОшибка: ФАЙЛ не найден");
            break;
        case MAIN_STRING_OVERFLOW:
            printf("\nОшибка: ФАЙЛ - одна из строк переполнена");
            break;
    }
}
typedef struct st
{
    char c;
    int a;
} st;
int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    printf("%zu\n", sizeof(st));
    if (argc != 2)
    {
        printf("Коректно - app.exe ./data.txt");
        return EXIT_FAILURE;
    }
    const char *name_file = argv[1];
    char buff[8];
    FILE *f;
    int rc = EXIT_SUCCESS;
    f = fopen(name_file, "r");
    if (f == NULL)
        rc = FILE_NOT_FOUND;
    else
    {
        st_travel countries[NUMBER_COUNTRY];
        st_key_travel key_arr[NUMBER_COUNTRY];
        size_t size_countries = 0, size_key = 0;
        rc = read_array_travel_country(f, countries, &size_countries);
        if (rc == FILE_IS_EMPTY)
            rc = EXIT_SUCCESS;
        fclose(f);
        print_add_err(rc);
        if (rc == EXIT_SUCCESS)
        {
            fill_key_arr(key_arr, &size_key, countries, size_countries);
            int step_menu = -1, rc_step = 0;
            //print_task();
            print_menu();
            while (step_menu != 0)
            {
                printf("\n---------------\n"
                       "Выберите пункт меню:");
                rc_step = scanf("%d", &step_menu);
                fgets(buff, 8, stdin);
                if (rc_step == 0)
                    printf("Нет такого пункта!");
                else if (step_menu == 1)
                {
                    if (size_countries == 0)
                        printf("\nДанные пустые!");
                    else
                    {
                        print_countries(countries, size_countries);
                        print_menu();
                    }
                }
                else if (step_menu == 2)
                {
                    rc = add_country(countries, &size_countries);
                    if (rc == EXIT_SUCCESS)
                    {
                        print_main_table();
                        print_travel_country(&countries[size_countries - 1]);
                        f = fopen(name_file, "w+");
                        rewrite_data(f, countries, size_countries);
                        fclose(f);
                        printf("Файл %s успешно изменен", name_file);
                    }
                }
                else if (step_menu == 3)
                {
                    if (size_countries == 0)
                        printf("\nДанные пустые!");
                    else
                    {
                        char del_str[STRING_COUNTRY];
                        printf("Введите название страны, которую нужно удалить: ");
                        fgets(del_str, STRING_COUNTRY + 2, stdin);
                        if (strlen(del_str) > STRING_COUNTRY)
                        {
                            printf("Переполнение строки для ввода название страны\n");
                            rc = COUNTRY_OVERFLOW;
                        }
                        else
                        {
                            if (del_str[strlen(del_str) - 1] == '\n')
                                del_str[strlen(del_str) - 1] = '\0';
                            int rc_del = 0;
                            rc_del = delete_country_on_name(countries, &size_countries, del_str);
                            if (rc_del) {
                                f = fopen(name_file, "w+");
                                rewrite_data(f, countries, size_countries);
                                fclose(f);
                                printf("Стран была удалена.");
                            }
                            else
                                printf("Такой страны нет.");

                        }
                    }
                }
                else if (step_menu == 4)
                {
                    if (size_countries == 0)
                        printf("\nДанные пустые.");
                    else
                    {
                        char materics[NUMBER_MATERIC][STRING_MATERIC] = { "Европа",
                                                                          "Азия",
                                                                          "Африка",
                                                                          "Южная Америка",
                                                                          "Северная Америка",
                                                                          "Океания"};
                        int materic_step = 0;
                        int rc_mat = 0;
                        printf("0 - Европа\n"
                               "1 - Азия\n"
                               "2 - Африка\n"
                               "3 - Южная Америка\n"
                               "4 - Северная Америка\n"
                               "5 - Океания\n");
                        printf("Выберите материк:");
                        rc_mat = scanf("%d", &materic_step);
                        fgets(buff, 8, stdin);
                        if (rc_mat == 1 || (materic_step <= 6 && materic_step >= 1))
                        {
                            char sport[STRING_SPORT] = { 0 };
                            st_key_travel key_find[NUMBER_COUNTRY];
                            size_t size_key_find = 0;
                            printf("Введите вид спорта: ");
                            fgets(sport, STRING_SPORT, stdin);
                            if (sport[strlen(sport) - 1] == '\n')
                                sport[strlen(sport) - 1] = '\0';
                            if (check_str_without_digits(sport))
                                fill_key_arr_find(key_find, &size_key_find, countries, size_countries, materics[materic_step], sport);
                            if (size_key_find == 0)
                                printf("Вид спорта спортивного туризма нет не в одной стране.");
                            else {
                                //print_table_key(key_arr, size_key);
                                print_countries_on_key(countries, key_find, size_key_find);
                                print_menu();
                            }
                        } else
                            printf("Нет такого значение для ввода или же материка.");
                    }
                }
                else if (step_menu == 5)
                {
                    if (size_countries == 0)
                        printf("\nДанные пустые.");
                    else
                    {
                        qiuck_sort_table(countries, 0, size_countries - 1);
                        fill_key_arr(key_arr, &size_key, countries, size_countries);
                        print_countries(countries, size_countries);
                        print_menu();
                    }
                }
                else if (step_menu == 6)
                {
                    if (size_countries == 0)
                        printf("\nДанные пустые.");
                    else
                    {
                        print_table_key(key_arr, size_key);
                        qiuck_sort_key(key_arr, 0, size_key - 1);
                        printf("Отсортированная ");
                        print_table_key(key_arr, size_key);
                        print_countries(countries, size_countries);
                        print_menu();
                    }
                }
                else if (step_menu == 7)
               {
                  printf("Замеры времени:\n");
                  fill_key_arr(key_arr, &size_key, countries, size_countries);
                  time_unsorted_arrays(countries, size_countries, key_arr, size_key);
                }
                else if (step_menu == 0)
                {
                    printf("До свидания!");
                }
                else
                    printf("Нет такого пункта!");
                if (rc != EXIT_SUCCESS)
                {
                    print_add_err(rc);
                    if (step_menu != 0)
                        rc = EXIT_SUCCESS;
                }
            }
        }
     }

    return rc;
}