#include "../inc/print_modelling_data.h"

void default_modeling_t(modeling_t *modeling)
{
    modeling->amount_input = 0;
    modeling->amount_output = 0;
    modeling->amount_calls = 0;

    modeling->model_time = 0.0;
    modeling->add_all = 0.0;
    modeling->consideration_all = 0.0;
    modeling->dowtime = 0.0;

    modeling->current_length_queue = 0;
    modeling->average_length_queue = 0.0;
    modeling->average_arrival_time = 0.0;
}

void print_model_data_between(const modeling_t *modeling, const model_params *params)
{
    printf("============= %d =================\n", modeling->amount_output);
    printf("┌─────────────────────────────────────┬────────────┐\n");
    printf("│    Количесвто вошедших заявок       │ %10d │\n", modeling->amount_input);
    printf("├─────────────────────────────────────┼────────────┤\n");
    printf("│    Количесвто вышедших заявок       │ %10d │\n", modeling->amount_output);
    printf("├─────────────────────────────────────┼────────────┤\n");
    printf("│  Текушая длина/Cредняя длина оч-ди  │ %3d / %3.1lf  │\n", modeling->current_length_queue, modeling->average_length_queue / (params->amount_iterations / 2.0) / modeling->amount_output);
    printf("├─────────────────────────────────────┼────────────┤\n");
    printf("│ Среднее время ожидание эл-та в оч-ди│   %.6lf │\n", modeling->average_arrival_time / modeling->amount_output);
    printf("└─────────────────────────────────────┴────────────┘\n");
}

void print_model_data(const modeling_t *modeling, const model_params *params)
{
    double t_consideration = params->amount_iterations * (params->consideration_t2 - params->consideration_t1) / 2.0 * params->amount_application;
    double t_add = (params->add_t2 - params->add_t1) / 2.0 * params->amount_application;
    double t_downtime = t_add - t_consideration;
    int t_amount_calls = params->amount_iterations * params->amount_application;

    double t_amount_application = modeling->model_time / ((params->add_t2 - params->add_t1) / 2.0);
    double t_measurement_input = 100.0 * fabs(modeling->amount_output - t_amount_application) / t_amount_application;
    double t_model_time = modeling->consideration_all + modeling->dowtime + 2;
    double t_measurement_output = 100.0 * fabs(modeling->model_time - t_model_time) / t_model_time;
    double t_measurement_model = 100.0 * fabs(modeling->model_time - t_add) / t_add;
    printf("\n================================== Результаты ==================================\n");
    printf("┌─────────────────────────────────────┬────────────────────┬────────────────────┐\n");
    printf("│             Название                │    Практические    │    Теоретические   │\n");
    printf("├─────────────────────────────────────┼────────────────────┼────────────────────┤\n");
    printf("│     Общее время моделирования       │ %13.6lf е.в. │ %10.0lf е.в.    │\n", modeling->model_time, t_add);
    printf("├─────────────────────────────────────┼────────────────────┼────────────────────┤\n");
    printf("│   Общее время добавления заявок     │ %13.6lf е.в. │ %10.0lf е.в.    │\n", modeling->add_all, t_add);
    printf("├─────────────────────────────────────┼────────────────────┼────────────────────┤\n");
    printf("│   Общее время обработки заявок      │ %13.6lf е.в. │ %10.0lf е.в.    │\n", modeling->consideration_all, t_consideration);
    printf("├─────────────────────────────────────┼────────────────────┼────────────────────┤\n");
    printf("│         Время простоя ОА            │ %13.6lf е.в. │ %10.0lf е.в.    │\n", modeling->dowtime, t_downtime);
    printf("├─────────────────────────────────────┼────────────────────┼────────────────────┤\n");
    printf("│      Количество срабатываний        │ %10d е.в.    │ %5d +- 5 е.в.    │\n", modeling->amount_calls, t_amount_calls);
    printf("├─────────────────────────────────────┴────────────────────┼────────────────────┤\n");
    printf("│                  Расчет погрешности                      │     Результат      │\n");
    printf("├──────────────────────────────────────────────────────────┼────────────────────┤\n");
    printf("│           -------Погрешность по входу--------            │                    │\n");
    printf("│  Количество заявок (Общее время модел-я / ср.приход)     │ %13.6lf е.в. │\n", t_amount_application);
    printf("│  100 * |Кол-во пришед. - Кол-во теорет| / Кол-во теорет. │ %10.6lf процент │\n", t_measurement_input);
    printf("├──────────────────────────────────────────────────────────┼────────────────────┤\n");
    printf("│           -------Погрешность по выходу--------           │                    │\n");
    printf("│  Теор. время модел-я (Время обработки + Время простоя)   │ %13.6lf е.в. │\n", t_model_time);
    printf("│  100 * |Практ. время модел-я - Теорит. | / Теорет.       │ %10.6lf процент │\n", t_measurement_output);
    printf("├──────────────────────────────────────────────────────────┼────────────────────┤\n");
    printf("│   -------Погрешность по времени моделирования--------    │                    │\n");
    printf("│  Теор. время моделирования (ср. приход * кол-во вышедших)│ %13.6lf е.в. │\n",  t_add);
    printf("│  100 * |Практ. время модел-я - Теорит. | / Теорет.       │ %10.6lf процент │\n", t_measurement_model);
    printf("└──────────────────────────────────────────────────────────┴────────────────────┘\n");
}