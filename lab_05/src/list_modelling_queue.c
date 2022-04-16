#include "../inc/list_modelling_queue.h"

void list_queue_modeling(const model_params *params, address_library_t *lib_address)
{
    double add_time, consideration_time = 0.0;
    int amount_of_passes = 0, temp_of_passes;
    modeling_t simulate;
    default_modeling_t(&simulate);

    int work_mode = 0;

    add_time = rand_double(params->add_t1, params->add_t2);
    simulate.add_all += add_time;

    list_queue_t ptr_queue;
    default_list_queue(&ptr_queue);

    int i = params->amount_between_print;
    while (simulate.amount_output < params->amount_application)
    {
        if (work_mode == 0)
        {
            if (ptr_queue.size != 0)
            {
                amount_of_passes = ptr_queue.head->data;

                add_address_free(lib_address, (size_t) ptr_queue.head);

                list_pop_application(&ptr_queue);
                consideration_time = rand_double(params->consideration_t1, params->consideration_t2);
                simulate.consideration_all += consideration_time;
                work_mode = 1;
                simulate.amount_calls++;
            }
            else
            {
                simulate.model_time += add_time;
                simulate.dowtime += add_time;
                amount_of_passes = 0;
                list_push_application(&ptr_queue, amount_of_passes);

                add_address_create(lib_address, (size_t) ptr_queue.head);

                add_time = rand_double(params->add_t1, params->add_t2);
                simulate.add_all += add_time;
                simulate.amount_input++;
            }
        }
        else
        {
            if (cmp_double(add_time, consideration_time) > 0)
            {
                add_time -= consideration_time;
                simulate.model_time += consideration_time;
                consideration_time = 0.0;
                work_mode = 0;
                amount_of_passes++;
                if (amount_of_passes < params->amount_iterations)
                {
                    list_push_application(&ptr_queue, amount_of_passes);
                    add_address_create(lib_address, (size_t) ptr_queue.head);
                }
                else
                {
                    simulate.amount_output++;
                    if (simulate.amount_output)
                        simulate.average_length_queue += ptr_queue.size;
                }
            }
            else
            {
                if (cmp_double(consideration_time, add_time) > 0)
                    simulate.average_arrival_time += (consideration_time - add_time) * ptr_queue.size;
                consideration_time -= add_time;
                simulate.model_time += add_time;
                temp_of_passes = 0;
                list_push_application(&ptr_queue, temp_of_passes);

                add_address_create(lib_address, (size_t) ptr_queue.head);

                simulate.amount_input++;

                add_time = rand_double(params->add_t1, params->add_t2);
                simulate.add_all += add_time;
            }

            if (simulate.amount_output == i && simulate.amount_output > 0)
            {
                simulate.dowtime = simulate.add_all - simulate.consideration_all;
                simulate.current_length_queue = simulate.amount_input - simulate.amount_output;
                print_model_data_between(&simulate, params);
                //printf("Элементы очереди, где значение означает номер прошедшей обработки ОА:\n   ");
                //print_list_application(ptr_queue);
                i += params->amount_between_print;
            }

        }
    }

    print_model_data(&simulate, params);
    free_list_application(&ptr_queue);
}
