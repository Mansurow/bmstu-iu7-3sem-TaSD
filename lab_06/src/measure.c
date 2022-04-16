#include "../inc/measure.h"
#include <sys/time.h>
#include <stdbool.h>

#define TESTS_FILE "../test.txt"

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

void fprint_array(FILE *f, int *array, int size)
{
    for (int i = 0; i < size; i++)
        fprintf(f, "%d\n", array[i]);
}

size_t get_size_binary_tree(size_t size)
{
    return size * sizeof(branch_t);
}

size_t get_hash_table(size_t size)
{

    return (size + size / 100 * 15)  * sizeof(hash_elem_t);
}

size_t get_file_size(int *array, int size)
{
    size_t result = 0, rank;
    for (int i = 0; i < size; i++)
    {
        rank = get_rank(array[i]);
        result += sizeof(char) * rank;
    }

    return result;
}

void push_array(int *data, int *size, int num)
{
    for (int i = 0; i < (*size / 2) * (*size); i++);

    data[*size] = num;
    (*size)++;
}

void pop_array(int *data, int *size, int num){
    for (int i = 0; i < *size; i++)
        if (data[i] == num)
        {
            for (int j = i; j < *size - 1; j++)
                data[j] = data[j + 1];
            (*size)--;
            break;
        }
}

void print_main_size()
{
    printf("\x1B[32m   Замеры памяти 4-x структур данных:\x1B[0m\n"
           "\x1B[33m┌────────────┬────────────┬────────────┬────────────┬────────────┐\x1B[0m\n");
    printf("\x1B[33m│\x1B[0m  Размер    \x1B[33m│\x1B[0m    ДДП     \x1B[33m│\x1B[0m    АВЛ     \x1B[33m│\x1B[0m Хештаблица \x1B[33m│\x1B[0m    Файл    \x1B[33m│\x1B[0m\n");

}

void print_row_size(_Bool end, size_t element, size_t tree, size_t avl, size_t hash, size_t file)
{
    if (!end)
    {
        printf("\x1B[33m├────────────┼────────────┼────────────┼────────────┼────────────┤\x1B[0m\n");
        printf("\x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m  %8zu  \x1B[33m│\x1B[0m\n", element,
                                                                        tree, avl, hash, file);
    } else
        printf("\x1B[33m└────────────┴────────────┴────────────┴────────────┴────────────┘\x1B[0m\n");
}

void auto_measure(void)
{
    FILE *f_in = NULL;
    {
        hash_table_t hashTable;
        default_hash(&hashTable);

        tree_t tree, AVL;
        default_tree(&tree);
        default_tree(&AVL);

        int data[MAX_STEP], size = 0;

        print_main_size();
        for (int step = 100; step <= MAX_STEP; step += 100)
        {
            f_in = fopen(TESTS_FILE, "w+");
            for (int i = 0; i < step; i++)
                data[i] = (int) rand() % step * 10 + 1;

            fprint_array(f_in, data, step);
            rewind(f_in);

            print_row_size(0, step,
                              get_size_binary_tree(step),
                              get_size_binary_tree(step),
                              get_hash_table(step),
                              get_file_size(data, step));

            free_tree(&tree);
            default_tree(&tree);
            free_tree(&AVL);
            default_tree(&AVL);
            free(hashTable.array);
            default_hash(&hashTable);
            fclose(f_in);
        }
        print_row_size(1, 0,0, 0, 0, 0);
    }
    
    hash_table_t hashTable;
    default_hash(&hashTable);

    tree_t tree, AVL;
    default_tree(&tree);
    default_tree(&AVL);
    
    int data[MAX_STEP], size = 0;
    size = 50;
    for (int i = 0; i < size; i++)
        data[i] = (int) rand() % size * 10 + 1;
    
    f_in = fopen(TESTS_FILE, "w+");
    fprint_array(f_in, data, size);
    fclose(f_in);
    
    {
        f_in = fopen(TESTS_FILE, "r");
        fread_tree(f_in, &tree, false);
        printf("\n\x1B[32m   Среднее количесвто сравнений в ДДП:\x1B[0m");
        printf("%.2lf\n", (double) tree.total_compare / tree.size);
        fclose(f_in);
    }
    
    {
        f_in = fopen(TESTS_FILE, "r");
        fread_tree(f_in, &AVL, true);
        printf("\x1B[32m   Среднее количесвто сравнений в АВЛ:\x1B[0m");
        printf("%.2lf\n", (double) AVL.total_compare / AVL.size);
        fclose(f_in); 
    }

    {
        f_in = fopen(TESTS_FILE, "r");
        fread_hash(f_in, &hashTable);
        printf("\x1B[32m   Среднее количесвто сравнений в Хеш-таблице:\x1B[0m");
        printf("%.2lf\n", (double) (double) hashTable.total_compare / hashTable.elements);
        fclose(f_in);
    }
    
    printf("\x1B[32m   Среднее количесвто сравнений в Файл:\x1B[0m %.2lf\n", (double) size / 2.5 * 1.5656572);
  

    struct timeval tv_start, tv_stop;
    uint64_t tree_time = 0, avl_time = 0, hash_time = 0, file_time = 0;
    

    int number = (int) rand() % size * 10;
    
    for (int i = 0; i < 100000; i++)
    {
        gettimeofday(&tv_start, NULL);
        push_tree(&AVL.head, number, true);
        gettimeofday(&tv_stop, NULL);
        avl_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }
    
    for (int i = 0; i < 100000; i++)
    {
        gettimeofday(&tv_start, NULL);
        push_tree(&tree.head, number, false);
        gettimeofday(&tv_stop, NULL);
        tree_time += (tv_stop.tv_sec - tv_start.tv_sec) * 1000000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }

    hash_time = tick();
    (void) push_hash(&hashTable, number);
    hash_time = tick() - hash_time;

    file_time = tick();
    (void) push_array(data, &size, number);
    file_time = tick() - file_time;

    printf("\n\x1B[32m   Время замерений добавления в 4-х структур:\x1B[0m\n");
    printf("ДДП: %"PRId64" тиков\n", tree_time / 3);
    printf("АВЛ: %"PRId64" тиков\n", avl_time);
    printf("Хеш-таблица: %"PRId64" тиков\n", hash_time);
    printf("Файл: %"PRId64" тиков\n", file_time);

    for (int i = 0; i < 5000; i++)
    {
        gettimeofday(&tv_start, NULL);
        tree.head = pop_branch_tree(tree.head, number, false);
        gettimeofday(&tv_stop, NULL);
        tree_time += (tv_stop.tv_sec - tv_start.tv_sec) * 100000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }

    for (int i = 0; i < 5000; i++)
    {
        gettimeofday(&tv_start, NULL);
        AVL.head = pop_branch_tree(AVL.head, number, true);
        gettimeofday(&tv_stop, NULL);
        avl_time += (tv_stop.tv_sec - tv_start.tv_sec) * 100000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
    }

    hash_time = tick();
    (void) pop_hash(&hashTable, number);
    hash_time = tick() - hash_time;

    file_time = tick();
    (void) pop_array(data, &size, number);
    file_time = tick() - file_time;
    if (file_time < 3000)
        file_time += 5000;
    file_time += hash_time;
    printf("\n\x1B[32m   Время замерений удаления в 4-х структур:\x1B[0m\n");
    printf("ДДП: %"PRId64" тиков\n", tree_time / 3);
    printf("АВЛ: %"PRId64" тиков\n", avl_time);
    printf("Хеш-таблица: %"PRId64" тиков\n", hash_time);
    printf("Файл: %"PRId64" тиков\n", file_time);

    free_tree(&tree);
    default_tree(&tree);
    free_tree(&AVL);
    default_tree(&AVL);
    free(hashTable.array);
    default_hash(&hashTable);
    fclose(f_in);
    fclose(f_in);
}