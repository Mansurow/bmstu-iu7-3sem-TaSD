#include "../inc/take_measure.h"

size_t get_size_array()
{
    return sizeof(array_queue_t);
}
size_t get_size_list(size_t n)
{
    return n * sizeof(node_queue_t);
}

void print_main_table_size()
{
    printf("\n"
           "┌──────────────────┬──────────────────┬──────────────────┐\n");
    printf("│     Размер       │      Массив      │      Список      │\n");
}
void print_table_size(size_t count, size_t array, size_t list)
{
    printf("├──────────────────┼──────────────────┼──────────────────┤\n");
    printf("│ %10zu       │ %10zu       │ %10zu       │\n", count, array, list);
}

void print_main_table_time()
{
    printf("\n"
           "┌──────────────────┬─────────────────────────────┬─────────────────────────────┐\n"
           "│                  │           Массив            │           Список            │\n"
           "│      Размер      ├──────────────┬──────────────┼──────────────┬──────────────┤\n"
           "│                  │  Добавление  │   Удаление   │  Добавление  │   Удаление   │\n");
}
void print_table_time(size_t count, int64_t time_push_array, int64_t time_pop_array, int64_t time_push_list, int64_t time_pop_list)
{
    printf("├──────────────────┼──────────────┼──────────────┼──────────────┼──────────────┤\n"
           "│ %10zu       │ %10"PRId64"   │ %10"PRId64"   │ %10"PRId64"   │ %10"PRId64"   │\n", count,
           time_push_array, time_pop_array,
           time_push_list, time_pop_list);
}

void analys_size_queue()
{

    print_main_table_size();
    for (int i = 0; i <= MAX_MEASURE; i += STEP_M)
    {
        size_t memory_array = get_size_array();
        size_t memory_list = get_size_list(i);
        print_table_size(i, memory_array, memory_list);
    }
    printf("└──────────────────┴──────────────────┴──────────────────┘\n");
}
void analys_time_queue()
{
    array_queue_t array;
    default_array_queue(&array);
    list_queue_t list;
    default_list_queue(&list);

    struct timeval tv_start, tv_stop;
    int64_t time = 0, elapsed_push_list = 0, elapsed_push_array = 0,
            elapsed_pop_list = 0, elapsed_pop_array = 0;

    print_main_table_time();
    int flag = 0;
    for (int i = 0; i <= MAX_MEASURE;)
    {
        for (int k = 0; k < I_S; k++)
        {
            for (int j = 0; j < i; j++)
            {
                gettimeofday(&tv_start, NULL);
                array_push_application(&array, j + 1);
                gettimeofday(&tv_stop, NULL);
                time = (tv_stop.tv_sec - tv_start.tv_sec) * 100000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
                elapsed_push_array += time;
            }

            for (int j = 0; j < i; j++)
            {
                gettimeofday(&tv_start, NULL);
                array_pop_application(&array);
                gettimeofday(&tv_stop, NULL);
                time = (tv_stop.tv_sec - tv_start.tv_sec) * 100000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
                elapsed_push_array += time;
            }

            for (int j = 0; j < i; j++)
            {
                gettimeofday(&tv_start, NULL);
                list_push_application(&list, j + 1);
                gettimeofday(&tv_stop, NULL);
                time = (tv_stop.tv_sec - tv_start.tv_sec) * 100000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
                elapsed_push_list += time;
            }
            for (int j = 0; j < i; j++)
            {
                gettimeofday(&tv_start, NULL);
                list_pop_application(&list);
                gettimeofday(&tv_stop, NULL);
                time = (tv_stop.tv_sec - tv_start.tv_sec) * 100000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
                elapsed_pop_list += time;
            }
            free_list_application(&list);
        }

        if (i > 0)
        {
            if (elapsed_push_array > 0)
                elapsed_push_array /= (I_S - 2);
            if (elapsed_pop_array > 0)
                elapsed_pop_array /= (I_S - 2);
            if (elapsed_push_list > 0)
                elapsed_push_list /= (I_S - 2);
            if (elapsed_pop_list > 0)
                elapsed_pop_list /= (I_S - 2);
        }
        print_table_time(i, elapsed_push_array, elapsed_pop_array, elapsed_push_list, elapsed_pop_list);
        if (i == 0)
            i = STEP;
        else
        {
            if (!flag)
            {
                i *= STEP / 2;
                flag = 1;
            }
            else
            {
                i /= (STEP / 2);
                i *= STEP;
                flag = 0;
            }
        }
    }
    printf("└──────────────────┴──────────────┴──────────────┴──────────────┴──────────────┘\n");
}