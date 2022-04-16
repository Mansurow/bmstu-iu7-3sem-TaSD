#include "../inc/array_modelling_queue.h"

void array_queue_modeling(const model_params *params)
{
    double add_time, consideration_time = 0.0;
    int amount_of_passes = 0, temp_of_passes;
    modeling_t simulate;
    default_modeling_t(&simulate);

    int work_mode = 0;
    int rc = EXIT_SUCCESS;
    add_time = rand_double(params->add_t1, params->add_t2);
    simulate.add_all += add_time;

    array_queue_t queue;
    default_array_queue(&queue);
    int i = params->amount_between_print;
    while (simulate.amount_output < params->amount_application && rc == 0)
    {
        if (work_mode == 0)
        {
            //если аппарат не работает
            //если в очереди есть элементы, то необходимо снять первый и запустить аппарат
            if (queue.size > 0)
            {
                amount_of_passes = *queue.head;
                array_pop_application(&queue);
                consideration_time = rand_double(params->consideration_t1, params->consideration_t2);
                simulate.consideration_all += consideration_time;
                work_mode = 1;
                simulate.amount_calls++;
            }
            else
            {
                //если в очереди нет элементов, нужно подождать, пока новый элемент войдет в очередь
                simulate.model_time += add_time;
                simulate.dowtime += add_time;
                amount_of_passes = 0;
                rc = array_push_application(&queue, amount_of_passes);
                add_time = rand_double(params->add_t1, params->add_t2);
                simulate.add_all += add_time;
                simulate.amount_input++;
            }
        }
        else
        {
            //если аппарат работает
            if (cmp_double(add_time, consideration_time) > 0)
            {
                //если заявка не успеет войти в очередь до того, как аппарат закончит работу
                //то заканчиваем время работы аппарата
                add_time -= consideration_time;
                simulate.model_time += consideration_time;
                consideration_time = 0.0;
                work_mode = 0;
                amount_of_passes++;
                //если из аппарата вышла заявка, которая проходила очередь меньше 5 раз, добавляем ее обратно
                if (amount_of_passes < params->amount_iterations)
                    rc = array_push_application(&queue, amount_of_passes);
                else
                {
                    simulate.amount_output++;
                    if (simulate.amount_output)
                        simulate.average_length_queue += queue.size;
                }
                //иначе она закончила свой цикл и вышла из системы
            }
//            else if (cmp_double(consideration_time, add_time) > 0 && params->consideration_t2 > params->add_t2)
//            {
//                consideration_time -= add_time;
//
//            }
            else
            {
                //если новая заявка успеет добавиться в очередь во время работы аппарата
                //вычитаем время захода из времени работы аппарата
                if (cmp_double(consideration_time, add_time) > 0)
                    simulate.average_arrival_time += (consideration_time - add_time) * queue.size;
                consideration_time -= add_time;
                simulate.model_time += add_time;
                temp_of_passes = 0;
                rc = array_push_application(&queue, temp_of_passes);
                simulate.amount_input++;

                add_time = rand_double(params->add_t1, params->add_t2);
                simulate.add_all += add_time;
            }

            if (simulate.amount_output == i && simulate.amount_output > 0)
            {
                simulate.current_length_queue = queue.size;
                print_model_data_between(&simulate, params);
                //printf("Элементы очереди, где значение означает номер прошедшей обработки ОА:\n   ");
                //print_array_application(&queue);
                i += params->amount_between_print;
            }
        }
    }
    if (rc == ARRAY_OVERFLOW)
        printf("Массив переполнен!\n");
    if (rc == EXIT_SUCCESS)
        print_model_data(&simulate, params);
}
