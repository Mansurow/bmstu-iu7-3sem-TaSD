#include "../inc/menu.h"

void input_step_menu(int *step, int min, int max)
{
    int rc = -1;
    char buff[BUFF_SIZE];
    while(rc != EXIT_SUCCESS)
    {
        printf("\nВведите команду: ");
        if (scanf("%d", step) != 1)
        {
            printf("Ошибка! Введен некорректный символ!\n");
            fgets(buff, sizeof(buff), stdin);
            rc = INVALID_DATA;
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

void print_menu()
{
    printf("\n=============Параметры по умолчанию==============\n"
           "- Время добавления от %.1lf до %.1lf\n"
           "- Время обработки от %.1lf до %.1lf\n"
           "- Количество выходных заявок %d заявок\n"
           "- Число промежуточного вывода %d заявок\n"
           "6 - Поменять время добавления\n"
           "7 - Поменять время обработки\n", ADD_T1, ADD_T2, CONS_T1, CONS_T2, AMOUNT_APPLICATION, AMOUNT_PRINT);
    printf("\n"
           "============MENU=============\n"
           "1 - Массив-Очередь\n"
           "2 - Список-Очередь\n"
           "3 - Выести информацию о использовании адрессов\n"
           "    при моделировании очереди - список\n"
           "4 - Замеры времени\n"
           "5 - Замеры памяти\n"
           "0 - Выход\n");
}