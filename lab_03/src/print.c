#include "structs_matrix.h"
#include "errors.h"
#include "print.h"

void print_main_menu()
{
    printf("\n--------------Меню--------------\n"
           "1 - Ввести матрицу\n"
           "2 - Ввести вектор-стоблец\n"
           "3 - Умножить матрицу на вектор\n"
           "4 - Вывести матрицы и вектор\n"
           "5 - Замерить эффективность\n"
           "0 - Выход\n");
}
void print_matrix_menu()
{
    printf("\n"
           "1 - Ввести матрицу в обычном ввиду\n"
           "2 - Ввести матрицу в разреженном ввиде\n"
           "3 - Автозаполение матрицы\n");
}
void print_vector_menu()
{
    printf("\n"
           "1 - Ввести вектор в обычном ввиду\n"
           "2 - Ввести вектор в разреженном ввиде\n"
           "3 - Автозаполение вектора\n");
}

void print_usual_matrix(const matrix_t *matrix)
{
    if (matrix->n > MAX_PRINT || matrix->m > MAX_PRINT)
        printf("Матрица слишком большая для вывода!.\n");
    else
    {
        for (int i = 0; i < matrix->n; i++) {
            for (int j = 0; j < matrix->m; j++)
                if (matrix->m == 1)
                    printf("│ %5d    |", matrix->matrix[i][j]);
                else if (j == 0)
                    printf("│ %5d    ", matrix->matrix[i][j]);
                else if (j == matrix->m - 1)
                    printf("%-5d │", matrix->matrix[i][j]);
                else
                    printf("%-5d ", matrix->matrix[i][j]);
            printf("\n");
        }
    }
}
void print_special_matrix(const special_matrix_t *matrix)
{
    printf("\n A = [");
    for (int i = 0; i < matrix->na; i++)
        printf(" %d", matrix->A[i]);
    printf(" ]\n");
    printf("JA = [");
    for (int i = 0; i < matrix->na; i++)
        printf(" %d", matrix->JA[i]);
    printf(" ]\n");
    printf("IA = [");
    for (int i = 0; i < matrix->n + 1; i++)
        printf(" %d", matrix->IA.list[i]);
    printf(" ]\n");
}
void print_special_vector(const special_vector_column_t *matrix)
{
    printf("\n A = [");
    for (int i = 0; i < matrix->na; i++)
        printf(" %d", matrix->A[i]);
    printf(" ]\n");
    printf("JA = [ ]\n");
    printf("IA = [");
    for (int i = 0; i < matrix->n + 1; i++)
        printf(" %d", matrix->IA.list[i]);
    printf(" ]\n");
}

void print_err_matrix(int rc)
{
    if (rc == INVALID_ERR)
        printf("   Ошибка! Значени введено не верно!");
    else if (rc == MATRIX_N_ERR)
        printf("   Ошибка! Значение размера [n] не входит в предел от %d до %d!\n", MIN_N, MAX_N);
    else if (rc == MATRIX_M_ERR)
        printf("   Ошибка! Значение размера [m] не входит в предел от %d до %d!\nw", MIN_M, MAX_M);
    else if (rc == MATRIX_MEMORY_ERR)
        printf("\n Ошибка! Память для матрицы не выделена!");
    else if (rc == PERCENT_ERR)
        printf("   Ошибка! Процент не может быть больше 100 процентов или быть меньне нуля!\n");
    else if (rc == STEP_ERR)
        printf("   Ошибка! Указанного пункта меню нет!");
    else if (rc == INDEX_NON_ZERO_ERR)
        printf("Ошибка! Элемент с такими индексами уже существует.\n");
    else if (rc == INDEX_NEGATIVE)
        printf("Ошибка! Индекс не может быть отрицательным или больше размера матрицы!\n");
    else if (rc == NON_ZERO_EL_ERR)
        printf("Ошибка! Введен нулевой элемент!\n");

}