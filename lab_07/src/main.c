#include "../inc/struct_graf.h"
#include "../inc/memory_graf.h"
#include "../inc/read_graf.h"
#include "../inc/print_graf.h"
#include "../inc/find_top.h"
#include "../inc/menu.h"
#include "../inc/measure_graf.h"

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    int rc = EXIT_SUCCESS;

    if (argc == 2) {
        FILE *f_in = fopen(argv[1], "r");
        if (f_in == NULL) {
            rc = FILE_NOT_FOUND;
            fclose(f_in);
        } else if (check_file(f_in)) {
            printf("ФАЙЛ пуст!\n");
            rc = FILE_IS_EMPTY;
        } else {
            st_matrix graf_matrix;
            default_matrix_graf(&graf_matrix);

            st_array_list graf_list;
            default_list_graf(&graf_list);

            uint64_t time = 0;
            _Bool is_read_matrix = 0, is_read_list = 0;
            char buff[8];
            int step = -1;
            print_menu();
            while (step != 0 && rc != MEMORY_ERROR)
            {
                if (step == 7 || step == 8 || step == 2 || step == 3 || step == 11)
                    print_menu();
                input_step_menu(&step, 0, 11);
                if (step == 0)
                {
                    free_matrix(&graf_matrix.matrix, graf_matrix.n);
                    free_array_list(&graf_list);
                    printf("До свидание!\n");
                }
                else if (step == 1)
                {
                    if (!is_read_matrix)
                    {
                        rc = read_file_matrix(f_in, &graf_matrix);
                        rewind(f_in);
                        if (rc == EXIT_SUCCESS)
                        {
                            is_read_matrix = 1;
                            printf("Данные успешно прочитанны!\n");
                        } else
                        {
                            if (rc == NOT_SQUERE_MATRIX)
                                printf("Матрица не квадратная!\n");
                            else
                                printf("Данные в файле некорректны!\n");
                        }
                    } else
                        printf("Данные прочитаны!\n");
                }
                else if (step == 2 || step == 3)
                {
                    if (is_read_matrix )
                    {
                        int top, len_way;
                        printf("\n");
                        input_top(&top, graf_matrix.n);
                        input_len(&len_way);
                        if (step == 2)
                        {
                            int dist[graf_matrix.n];
                            time = tick();
                            (void) algoritm_ballman_fold_matrix(&graf_matrix, top, dist);
                            time = tick() - time;
                            print_top_as_input(dist, graf_matrix.n, len_way, top);
                            printf("\x1b[33mВремя работы алгоритма Беллмана-Форда(массив): %"PRId64" тиков\033[0m", time);
                        } else if (step == 3)
                        {
                            int dist[graf_matrix.n];
                            time = tick();
                            (void) algoritm_dijkstra_matrix(&graf_matrix, top, dist);
                            time = tick() - time;
                            print_top_as_input(dist, graf_matrix.n, len_way, top);
                            printf("\x1b[33mВремя работы алгоритма Дейкстры(массив): %"PRId64" тиков\033[0m", time);
                        }
                    } else
                        printf("Граф пуст!\n");
                }
                else if (step == 4)
                {
                    print_matrix(&graf_matrix);
                }
                else if (step == 5)
                {
                    FILE *write_file = fopen("matrix.dot", "w");
                    print_graphviz_matrix(write_file, &graf_matrix);
                    fclose(write_file);
                    if (graf_matrix.matrix && graf_matrix.n)
                    {
                        system("dot -Tpng -O matrix.dot");
                        system("matrix.dot.png");
                    }
                }
                else if (step == 6)
                {
                    if (!is_read_list)
                    {
                        rc = read_file_list(f_in, &graf_list);
                        rewind(f_in);
                        if (rc == EXIT_SUCCESS)
                        {
                            is_read_list = 1;
                            printf("Данные успешно прочитанны!\n");
                        } else
                        {
                            if (rc == NOT_SQUERE_MATRIX)
                                printf("Матрица не квадратная!\n");
                            else
                                printf("Данные в файле некорректны!\n");
                        }
                    } else
                        printf("Данные прочитаны!\n");
                }
                else if (step == 7 || step == 8)
                {
                    if (is_read_list)
                    {
                        int top, len_way;
                        printf("\n");
                        input_top(&top, graf_list.n);
                        input_len(&len_way);
                        if (step == 7)
                        {
                            int dist[graf_list.n];
                            time = tick();
                            (void) algoritm_ballman_fold_list(&graf_list, top, dist);
                            time = tick() - time;
                            print_top_as_input(dist, graf_list.n, len_way, top);
                            printf("\x1b[33mВремя работы алгоритма Беллмана-Форда(список): %"PRId64" тиков\033[0m", time);
                        } else if (step == 8)
                        {
                            int dist[graf_list.n];
                            time = tick();
                            (void) algoritm_dijkstra_list(&graf_list, top, dist);
                            time = tick() - time;
                            print_top_as_input(dist, graf_list.n, len_way, top);
                            printf("\x1b[33mВремя работы алгоритма Дейкстры(список): %"PRId64" тиков\033[0m", time);
                        }
                    } else
                        printf("Граф пуст!\n");
                }
                else if (step == 9)
                {
                    print_array_list(&graf_list);
                }
                else if (step == 10)
                {
                    FILE *write_file = fopen("list.dot", "w");
                    print_graphviz_list(write_file, &graf_list);
                    fclose(write_file);
                    if (graf_list.array && graf_list.n)
                    {
                        system("dot -Tpng -O list.dot");
                        system("list.dot.png");
                    }
                }
                else if (step == 11)
                {
                    auto_measure();
                }
            }
        }
    } else
    {
        printf("Чтобы вести название файла - ./app.exe [filename]\n");
        rc = ARGV_ERR;
    }
    return rc;
}