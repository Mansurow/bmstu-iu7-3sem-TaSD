#include "../inc/menu.h"

void print_menu(void)
{
    printf("\n======================Menu====================\n"
           " - Массив смежности:\n"
           "    1 Прочитать данные в массив\n"
           "    Найти все вершины графа\n"
           "    не длинее указанного пути:\n"
           "        2 Алгоритм Беллмана-Форда\n"
           "        3 Алгоритм Дейкстры\n"
           "    4 Вывести матрицу\n"
           "    5 Вывести графически\n"
           " - Список смежности:\n"
           "    6 Прочитать данные в список\n"
           "    Найти все вершины графа\n"
           "    не длинее указанного пути\n"
           "        7 Алгоритм Беллмана-Форда\n"
           "        8 Алгоритм Дейкстры\n"
           "    9 Вывести список\n"
           "    10 Вывести графически\n"
           " - Эффективность:\n"
           "    11  Память и время\n"
           "==================================================\n");
}

void input_step_menu(int *step, int min, int max)
{
    int rc = -1;
    char buff[8];
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

void input_top(int *top, int n)
{
    int res = -1;
    char buff[8];
    while (res != 0)
    {
        printf("Введите вершину: ");
        res = scanf("%d", top);
        if (res == 0)
        {
            printf("    Ошибка! Введено не число!\n");
            fgets(buff, 8, stdin);
            res = 1;
        } else if (*top <= 0 || *top > n)
            printf("   Ошибка! В графе нет такой вершины!\n");
        else
            res = 0;
    }
}

void input_len(int *len_way)
{
    int res = -1;
    char buff[8];
    while (res != 0)
    {
        printf("Введите длину максимального пути: ");
        res = scanf("%d", len_way);
        if (res == 0)
        {
            printf("    Ошибка! Введено не число!\n");
            fgets(buff, 8, stdin);
            res = 1;
        } else if (*len_way <= 0)
            printf("    Ошибка! Путь не может быть отрицательным!\n");
        else
            res = 0;
    }
}