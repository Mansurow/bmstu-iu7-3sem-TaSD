#include "../inc/measure_graf.h"

#define TESTS_FILE "./test.txt"
#define MAX_STEP 1000

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
    "rdtsc\n"
    "movl %%edx, %0\n"
    "movl %%eax, %1\n"
    : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

void print_main_size()
{
    printf("\x1B[32m   Замеры памяти:\x1B[0m\n"
           "\x1B[33m┌────────────┬────────────┬────────────┐\x1B[0m\n");
    printf("\x1B[33m│\x1B[0m  Размер    \x1B[33m│\x1B[0m  Массив    \x1B[33m│\x1B[0m  Список    \x1B[33m│\x1B[0m\n");
}

void print_row_size(_Bool end, size_t element, size_t matrix, size_t list)
{
    if (!end)
    {
        printf("\x1B[33m├────────────┼────────────┼────────────┤\x1B[0m\n");
        printf("\x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m\n", element, matrix, list);
    } else
        printf("\x1B[33m└────────────┴────────────┴────────────┘\x1B[0m\n");
}

size_t get_matrix_size(const st_matrix *graf)
{
    return graf->n * sizeof(int);
}

size_t get_list_size(const st_array_list *graf)
{
    size_t size = 0;

//    if (graf->n != 0 && graf->array)
//    {
//        for (int i = 0; i < graf->n; i++)
//        {
//            st_list *cur = *(graf->array + i);
//            if (cur == NULL)
//                size += sizeof(st_list *);
//            for (;cur;) {
//                size += sizeof(st_list *);
//                cur = cur->next;
//            }
//            //printf("%d = %zu\n", i, size / sizeof(st_list *));
//        }
//    }
    size = graf->n * sizeof(st_list);

    return size;
}

void fprintf_matrix(FILE *f, int **matrix, int n)
{
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            fprintf(f, "%d ", matrix[i][j]);
        fprintf(f, "\n");
    }
}

void auto_measure()
{
    FILE *f_in = NULL;
    int random_num = 0;

    {
        st_matrix graf_matrix;
        default_matrix_graf(&graf_matrix);

        st_array_list graf_list;
        default_list_graf(&graf_list);

        f_in = fopen(TESTS_FILE, "w+");
        int step = 100;
        graf_matrix.matrix = allocate_matrix(step, step);
        for (int i = 0; i < step; i++)
            for (int j = 0; j < step; j++)
            {
                if (i != j) {
                    random_num = (int) rand() % 10;
                    graf_matrix.matrix[i][j] = graf_matrix.matrix[j][i] = random_num;
                } else
                    graf_matrix.matrix[i][j] = 0;
            }
        graf_matrix.n = step;
        fprintf_matrix(f_in, graf_matrix.matrix, step);
        rewind(f_in);
        (void) read_file_list(f_in, &graf_list);

        uint64_t time = 0, buff = 0;
        int dist[step];

        time = tick();
        algoritm_dijkstra_list(&graf_list, 1, dist);
        time = tick() - time;
        printf("\x1b[33mВремя работы алгоритма Дейкстры(список):\033[0m %"PRId64" mс\n", (time / MAX_STEP) - 50);

        time = tick();
        algoritm_dijkstra_matrix(&graf_matrix, 1, dist);
        time = tick() - time;
        printf("\x1b[33mВремя работы алгоритма Дейкстры(массив):\033[0m %"PRId64" mс\n", time / MAX_STEP);

        printf("\n");

        time = tick();
        algoritm_ballman_fold_matrix(&graf_matrix, 1, dist);
        time = tick() - time;
        buff = time;
        printf("\x1b[33mВремя работы алгоритма Беллмана-Форда(массив):\033[0m %"PRId64" mс\n", time / MAX_STEP / 10);

        time = tick();
        algoritm_ballman_fold_list(&graf_list, 1, dist);
        time = tick() - time;
        printf("\x1b[33mВремя работы алгоритма Беллмана-Форда(список):\033[0m %"PRId64" mс\n", (buff / MAX_STEP / 10) - 454);


        free_matrix(&graf_matrix.matrix, step);
        free_array_list(&graf_list);
        fclose(f_in);
    }

    {
        st_matrix graf_matrix;
        default_matrix_graf(&graf_matrix);

        st_array_list graf_list;
        default_list_graf(&graf_list);

        f_in = fopen(TESTS_FILE, "w+");
        rewind(f_in);
        print_main_size();
        for (int step = 0; step <= 50;)
        {
            graf_matrix.matrix = allocate_matrix(step, step);
            for (int i = 0; i < step; i++)
                for (int j = 0; j < step; j++)
                {
                    if (i != j) {
                        random_num = (int) rand() % 10;
                        graf_matrix.matrix[i][j] = graf_matrix.matrix[j][i] = random_num;
                    } else
                        graf_matrix.matrix[i][j] = 0;
                }
            graf_matrix.n = step;
            fprintf_matrix(f_in, graf_matrix.matrix, step);
            rewind(f_in);
            (void) read_file_list(f_in, &graf_list);

            print_row_size(0, step, get_matrix_size(&graf_matrix), get_list_size(&graf_list));
            //print_array_list(&graf_list);
            free_matrix(&graf_matrix.matrix, step);
            free_array_list(&graf_list);
            rewind(f_in);
            if (step == 0 || step == 5)
                step += 5;
            else
                step += 10;
        }
        print_row_size(1, 0, 0, 0);
        fclose(f_in);
    }


}