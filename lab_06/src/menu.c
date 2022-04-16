#include "../inc/menu.h"

void print_menu(void)
{
    printf("\n======================Menu====================\n"
           " - Trees:\n"
           "    1 Прочитать данные в дерево\n"
           "    2 Сбалансировать дерево\n"
           "    3 Добавить элемент\n"
           "    4 Удалить элемент\n"
           "    5 Поиск элемента\n"
           "    6 Вывести дерево\n"
           " - Hash:\n"
           "    7 Прочитать данные в Хештаблицу\n"
           "    8 Добавить элемент\n"
           "    9 Удалить элемент\n"
           "    10 Поиск элемента\n"
           "    11 Вывести Хештаблицу\n"
           " - Эффективность:\n"
           "    12  Память и время\n"
           "==================================================\n");
}

void input_step_menu(int *step, int min, int max)
{
    int rc = -1;
    char buff[BUFF_SIZE];
    while(rc != EXIT_SUCCESS)
    {
        printf("Введите команду: ");
        if (scanf("%d", step) != 1)
        {
            printf("Ошибка! Введен некорректный символ!\n");
            fgets(buff, sizeof(buff), stdin);
            rc = INVALID_ERR;
        }
        else if (*step > max || *step < min)
        {
            printf("Ошибка! Такого пункта нет!\n");
            rc = STEP_ERROR;
        }
        else
            rc = EXIT_SUCCESS;
    }
}

int check_file(FILE *f)
{
    int rc = EXIT_SUCCESS;
    if (f == NULL)
        rc = FILE_NOT_FOUND;
    else
    {
        long size;
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        if (size == 0)
        {
            rc = FILE_IS_EMPTY;
            fclose(f);
        }
        else
            fseek(f, 0, SEEK_SET);
    }

    return rc;
}

void input_number(int *number)
{
    int rc = -1;
    char buff[BUFF_SIZE];
    while(rc != EXIT_SUCCESS)
    {
        printf("Введите число: ");
        if (scanf("%d", number) != 1)
        {
            printf("Ошибка! Введен некорректный символ!\n");
            fgets(buff, sizeof(buff), stdin);
            rc = INVALID_ERR;
        }
        else
            rc = EXIT_SUCCESS;
    }
}