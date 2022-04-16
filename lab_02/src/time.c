#include "utils.h"
#include "time.h"
#include "sorts.h"

#define I_STEP 10000
#define SIZE 600
#define REPEAT 14

void make_table(void)
{
    printf("+--------+--------+-------------------+-------------------+--------------+--------+\n");
    printf("| %6s | %6s | %12s | %12s | %12s | %6s |\n", "I", "Размер","Размер 1 эл-та(б)", "Размер массива(б)", "BUBLE FLAG", "INSERT");
    printf("+--------+--------+-------------------+-------------------+--------------+--------+\n");
}

void make_data(int i, size_t size, size_t count_size_array, size_t one_element, int64_t time_1, int64_t time_2)
{
    printf("| %6d | %6zu | %17zu | %17zu | %12" PRId64 " | %6" PRId64 " |\n", i, size, one_element, count_size_array,  time_1, time_2);
    printf("+--------+--------+-------------------+-------------------+--------------+--------+\n");
}

void my_cpy_st_travel(st_travel *arr_cp, st_travel *arr_src, size_t n, int repeat)
{
    int step = 0;
    for (size_t i = 0; step < n * repeat; i++)
    {
        if (i == n - 1)
            i = 0;
        arr_cp[step++] = arr_src[i];
    }
}

void my_cpy_st_key(st_key_travel *arr_cp, st_key_travel *arr_src, size_t n, int repeat)
{
    int step = 0;
    for (size_t i = 0; step < n * repeat; i++)
    {
        if (i == n - 1)
            i = 0;
        arr_cp[step++] = arr_src[i];
    }
}

void time_unsorted_arrays(st_travel *countries, size_t n_c, st_key_travel *key, size_t n_k)
{
    struct timeval tv_start, tv_stop;
    int64_t time_b, time_i, elapsed_b_c = 0, elapsed_i_c = 0, elapsed_b_k = 0, elapsed_i_k = 0;
    printf("\nСравнение buble_sort и insert - протая таблица.\n");
    make_table();

    st_travel arr_b_c[SIZE];
    st_travel arr_i_c[SIZE];
    my_cpy_st_travel(arr_b_c, countries, n_c, REPEAT);
    my_cpy_st_travel(arr_i_c, countries, n_c, REPEAT);

    for (int i = 0; i <= I_STEP; i++)
    {
        gettimeofday(&tv_start, NULL);
        buble_sort_flag_table(arr_b_c, n_c * REPEAT);
        gettimeofday(&tv_stop, NULL);
        time_b = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        elapsed_b_c += time_b;

        gettimeofday(&tv_start, NULL);
        insert_sort_table(arr_i_c, n_c * REPEAT);
        gettimeofday(&tv_stop, NULL);

        time_i = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        elapsed_i_c += time_i;
    }
    elapsed_b_c = elapsed_b_c / (I_STEP - 2.0) * 100.0;
    elapsed_i_c = elapsed_i_c / (I_STEP - 2.0) * 100.0;
    make_data(I_STEP, n_c * REPEAT, n_c * REPEAT * sizeof(st_travel), sizeof(st_travel), elapsed_b_c, elapsed_i_c);

    printf("\nСравнение buble_sort и insert  - испол. таблицу ключей\n");
    make_table();

    st_key_travel arr_b_k[SIZE];
    st_key_travel arr_i_k[SIZE];
    my_cpy_st_key(arr_b_k, key, n_k, REPEAT);
    my_cpy_st_key(arr_i_k, key, n_k, REPEAT);

    for (int i = 0; i <= I_STEP; i++)
    {
        gettimeofday(&tv_start, NULL);
        buble_sort_flag_key(arr_b_k, n_k * REPEAT);
        gettimeofday(&tv_stop, NULL);
        time_b = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        elapsed_b_k += time_b;

        gettimeofday(&tv_start, NULL);
        insert_sort_key(arr_i_k, n_k * REPEAT);
        gettimeofday(&tv_stop, NULL);

        time_i = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        elapsed_i_k += time_i;
    }
    elapsed_b_k = elapsed_b_k / (I_STEP - 2.0) * 100.0;
    elapsed_i_k = elapsed_i_k / (I_STEP - 2.0) * 100.0;
    make_data(I_STEP, n_k * REPEAT, n_k * REPEAT * sizeof(st_key_travel), sizeof(st_key_travel), elapsed_b_k, elapsed_i_k);

    double fect_memory = (sizeof(st_key_travel) * 100.0) / sizeof(st_travel);
    double fect_time_b = 100.0 - (elapsed_b_k * 100.0) / elapsed_b_c;
    double fect_time_i = 100.0 - (elapsed_i_k * 100.0) / elapsed_i_c;
    printf("Эффективность таблицы ключей: \n");
    printf("Пaмять - %.1lf от всей таблицы\n", fect_memory);
    printf("Buble_sort - %.1lf\n", fect_time_b);
    printf("Insert_sort - %.1lf\n", fect_time_i);
}

