#include "../inc/struct_params.h"

void default_model_params(model_params *params)
{
    params->add_t1 = ADD_T1;
    params->add_t2 = ADD_T2;
    params->consideration_t1 = CONS_T1;
    params->consideration_t2 = CONS_T2;

    params->amount_application = AMOUNT_APPLICATION;
    params->amount_between_print = AMOUNT_PRINT;
    params->amount_iterations = MAX_ITER;
}
void change_add_time(model_params *params)
{
    int rc = 1;
    while (rc != 0)
    {
        printf("Введите время добавления (t1 t2): ");
        if (scanf("%lf", &params->add_t1) == 0 || scanf("%lf", &params->add_t2) == 0)
        {
            char buff[BUFF_SIZE];
            fgets(buff, sizeof(buff), stdin);
            rc = INVALID_DATA;
            printf("  Ошибка! Значение введены не верно - символ!\n");
        }
        else if (params->add_t1  >= params->add_t2 || (params->add_t1 == 0 && params->add_t2 == 0))
        {
            rc = INVALID_DATA;
            printf("  Ошибка! Значение введены не верно - от %.0lf до %.0lf!\n", params->add_t1, params->add_t2);
        }
        else
        {
            rc = EXIT_SUCCESS;
            printf("  Время успешно измененно - от %.0lf до %.0lf!\n", params->add_t1, params->add_t2);
        }
    }
}
void change_cons_time(model_params *params)
{
    int rc = 1;
    while (rc != 0)
    {
        printf("Введите время обработки (t1 t2): ");
        if (scanf("%lf", &params->consideration_t1) == 0 || scanf("%lf", &params->consideration_t2) == 0)
        {
            char buff[BUFF_SIZE];
            fgets(buff, sizeof(buff), stdin);
            rc = INVALID_DATA;
            printf("  Ошибка! Значение введены не верно - символ!\n");
        }
        else if (params->consideration_t1  >= params->consideration_t2 || (params->consideration_t1 == 0 && params->consideration_t2 == 0))
        {
            rc = INVALID_DATA;
            printf("  Ошибка! Значение введены не верно - от %.0lf до %.0lf!\n", params->consideration_t1, params->consideration_t2);
        }
        else
        {
            rc = EXIT_SUCCESS;
            printf("  Время успешно измененно - от %.0lf до %.0lf!\n", params->consideration_t1, params->consideration_t2);
        }
    }
}