#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <inttypes.h>

#define SIZE_STACK 1501

#define EMPTY_STACK  2
#define INVALID_ERR  3
#define STEP_ERR     4


#define STACK_OVERFLOW 10

#define MEMORY_ERR  20
#define MEMORY_COPY_ERR   21
#define MEMORY_LIST_PUSH  22


#define POLINROM    30
#define NO_POLIDROM 31

#define I_STEP 1000
typedef struct stack_array
{
    char *string;
    int size;
} stack_array_t;

typedef struct node_el
{
    int size_stack;
    char symbol;
    struct node_el *next;
} stack_list_t;

void print_error(int rc)
{
    switch (rc)
    {
        case EMPTY_STACK:
            printf("Cтэк пуст.\n");
            break;
        case INVALID_ERR:
            printf("Ошибка! Пункт меню введен не верно.\n");
            break;
        case STACK_OVERFLOW:
            printf("Ошибка! Стэк переполнен.\n");
            break;
        case MEMORY_ERR:
            printf("Ошибка! Память не выделена.\n");
            break;
    }
}

void defaul_stack_array_t (stack_array_t *stack)
{
    stack->size = 0;
    stack->string = NULL;
}
char *allocate_array_char(int size_array)
{
    char *chars = (char *) malloc(size_array * sizeof(char));
    if (!chars)
        return NULL;
    return chars;
}
void free_stack_array(stack_array_t *stack)
{
    free(stack->string);
    stack->string = NULL;
    stack->size = 0;
}
int push_array(stack_array_t *stack, const char symbol)
{
    int rc = EXIT_SUCCESS;
    if (stack->size >= SIZE_STACK)
        rc = STACK_OVERFLOW;
    else
    {
//        char *ptr = realloc(stack->string, (stack->size + 2) * sizeof(char));
//        if (!ptr)
//            rc = MEMORY_ERR;
//        else
//        {
//            stack->string = ptr;
//            ptr = NULL;
        stack->string[stack->size++] = symbol;
        stack->string[stack->size] = '\0';
//        }
    }
    return rc;
}
int input_stack_array(stack_array_t *stack)
{
    int rc = EXIT_SUCCESS;
    char symbol;
    printf("\nСтроку для проверки полиндрома.\n");
    printf("Введите последовательность символов, оканчивающихся точкой или перевод на следующую строку: ");
    while ((symbol = getchar()) != '.' && symbol != '\n' && rc == 0 )
    {
        if (push_array(stack, symbol) != EXIT_SUCCESS)
            rc = STACK_OVERFLOW;
    }
    return rc;
}
char pop_array(stack_array_t *stack)
{
    stack->size--;
    return stack->string[stack->size];
}
int copy_stack_array(stack_array_t *copy, stack_array_t *den)
{
    int rc = EXIT_SUCCESS;
    copy->string = (char *) malloc(den->size * sizeof(char));
    if (!copy->string)
        rc = MEMORY_COPY_ERR;
    else
    {
        copy->size = den->size;
        strcpy(copy->string, den->string);
        copy->string[copy->size] = '\0';
    }

    return rc;
}
int print_stack_array(stack_array_t *stack)
{
    int rc = EXIT_SUCCESS;
    stack_array_t copy_stack;
    defaul_stack_array_t(&copy_stack);
    if (stack->size == 0)
        rc = EMPTY_STACK;
    else
    {

        rc = copy_stack_array(&copy_stack, stack);
        if (rc == EXIT_SUCCESS)
        {
            printf("\nТекущее состояние стека, реализованного при помощи массива:\n");

            while (copy_stack.size)
            {
                printf("Адресс элемета: %p\n", &(copy_stack.string[copy_stack.size - 1]));
                if (copy_stack.string[copy_stack.size - 2] == -48)
                    printf("Значение элемнета: %c%c\n", pop_array(&copy_stack), pop_array(&copy_stack));
                else
                    printf("Значение элемнета: %c\n", pop_array(&copy_stack));
            }
        }
        free_stack_array(&copy_stack);
    }
    return rc;
}
int stack_array_is_palindrom(stack_array_t *stack)
{
    stack_array_t copy_stack;
    defaul_stack_array_t(&copy_stack);
    char symbol;
    int rc = EXIT_SUCCESS;
    int size = stack->size;
    copy_stack.string = allocate_array_char(size / 2);
    for (int i = 0; i < size / 2 && rc == 0; i++)
    {
        symbol = pop_array(stack);
        rc = push_array(&copy_stack, symbol);
    }
    if (rc == EXIT_SUCCESS)
    {
        for (int i = 0; i < size % 2; i++)
            pop_array(stack);

        for (int i = 0; i < stack->size; i++)
        {
            if (pop_array(stack) != pop_array(&copy_stack))
                return NO_POLIDROM;
        }
        free_stack_array(stack);
    } else
        return rc;
    return POLINROM;
}
stack_list_t *symbol_create(const char symbol)
{
    stack_list_t *node = malloc(sizeof(stack_list_t));
    if (node)
    {
        node->symbol = symbol;
        node->size_stack = 1;
        node->next = NULL;
    }

    return node;
}
void free_stack_list(stack_list_t **node)
{
    if (*node != NULL)
    {
        stack_list_t *head;
        for (; (*node)->next; *node = head)
        {
            head = (*node)->next;
            free(*node);
        }
        free(*node);
        head = NULL;
        *node = NULL;
    }
}
int push_stack_list_t(stack_list_t **head, const char symbol)
{
    int rc = EXIT_SUCCESS;
    if ((*head)->size_stack >= SIZE_STACK)
        rc = STACK_OVERFLOW;
    else
    {
        stack_list_t *node = symbol_create(symbol);

        if (node)
        {
            node->size_stack = (*head)->size_stack + 1;
            node->next = *head;
            *head = node;
        }
    }

    return rc;
}
int input_stack_list_t(stack_list_t **stack_head)
{
    char symbol;
    int rc = EXIT_SUCCESS;
    printf("\nСтроку для проверки полиндрома.\n");
    printf("Введите последовательность символов, оканчивающихся точкой или перевод на следующую строку: ");
    while((symbol = getchar()) != '.' && symbol != '\n')
    {
        if ((*stack_head)->size_stack == 0)
            *stack_head = symbol_create(symbol);
        else
        {
            if (push_stack_list_t(stack_head, symbol) != EXIT_SUCCESS)
                rc = STACK_OVERFLOW;
        }
    }
    if ((*stack_head)->size_stack == 0)
       *stack_head = NULL;
    return rc;
}
void defaul_stack_list_t(stack_list_t *stack)
{
    stack->size_stack = 0;
    stack->next = NULL;
}

stack_list_t *copy_stack_list_t(stack_list_t *den)
{
    stack_list_t *tail = NULL, *head = NULL, *current = den;
    while (current != NULL)
    {
        if (head == NULL)
        {
            head = (stack_list_t *) malloc(sizeof(stack_list_t));
            head->size_stack = current->size_stack;
            head->symbol = current->symbol;
            head->next = NULL;
            tail = head;
        } else
        {
            tail->next = (stack_list_t *) malloc(sizeof(stack_list_t));
            tail = tail->next;
            tail->size_stack = current->size_stack;
            tail->symbol = current->symbol;
            tail->next = NULL;
        }
        current = current->next;
    }
    return head;
}
int pop_stack_list(stack_list_t **stack_head)
{
    int rc = EXIT_SUCCESS;
    if (*stack_head == NULL)
        rc = EMPTY_STACK;
    else
    {
        stack_list_t *temp = *stack_head;
        *stack_head = (*stack_head)->next;
        if (temp->size_stack == 1)
            *stack_head = NULL;
        free(temp);
    }

    return rc;
}
int print_stack_list_t(stack_list_t *stack_head)
{
    int rc = EXIT_SUCCESS;
    if(stack_head == NULL)
        rc = EMPTY_STACK;
    else
    {
        stack_list_t copy_stack, *copy_list = &copy_stack;
        stack_list_t *head;
        defaul_stack_list_t(copy_list);
        copy_list = copy_stack_list_t(stack_head);
        printf("\nТекущее состояние стека, реализованного при помощи списка:\n");
        for (; copy_list->next; copy_list = head)
        {
            head = copy_list->next;
            printf("Адресс элемента: %p\n", copy_list);
            printf("Значение элемента: %c\n", copy_list->symbol);
            (void) pop_stack_list(&copy_list);
        }
        printf("Адресс элемента: %p\n", copy_list);
        printf("Значение элемента: %c\n", copy_list->symbol);
    }
    return rc;
}
int stack_list_is_palindrom(stack_list_t **stack_head)
{
    int rc = POLINROM;
    int size = (*stack_head)->size_stack;
    char symbol;
    stack_list_t add, *add_head = &add;
    defaul_stack_list_t(add_head);
    for (int i = 0; i < size / 2; i++)
    {
        symbol = (*stack_head)->symbol;
        pop_stack_list(stack_head);
        push_stack_list_t(&add_head, symbol);
    }
    for (int i = 0; i < size % 2; i++)
        pop_stack_list(stack_head);

    for (int i = 0; i < size / 2; i++)
    {
        if ((*stack_head)->symbol != add_head->symbol)
            rc = NO_POLIDROM;

        pop_stack_list(stack_head);
        pop_stack_list(&add_head);
    }
    return rc;
}

void print_conditions(void)
{
    printf("%s",
           "\nПрограмма предназначена для работы со стеком, реализованным при помощи массива или списка.\n"
           "Программа при помощи стека определяет, является ли строка палиндромом.\n"
           "Правила ввода строки : вводить символы без пробелов и завершить ввод симовлом '.' или нажать Enter(перевод на следующую строку)\n"
           "Максимальный размер стека - 1500 * sizeof(char).\n");
}
void print_menu(void)
{
    printf("%s",
           "\n===================================СТЕК_МАССИВ==========================================\n"
           "|| Выберите номер пункта меню для работы со стеком, реализованным при помощи МАССИВА: ||\n"
           "|| 1. Ввести стек                                                                     ||\n"
           "|| 2. Добавить элемент в стек(push)                                                   ||\n"
           "|| 3. Удалить элемент из стека(pop)                                                   ||\n"
           "|| 4. Определить, является ли строка палиндромом                                      ||\n"
           "|| 5. Вывести стек                                                                    ||\n"
           "=====================================СТЕК_СПИСОК========================================\n");
    printf("%s",
           "|| Выберите номер пункта меню для работы со стеком, реализованным при помощи СПИСКА:  ||\n"
           "|| 6. Ввести стек                                                                     ||\n"
           "|| 7. Добавить элемент в стек(push)                                                   ||\n"
           "|| 8. Удалить элемент из стека(pop)                                                   ||\n"
           "|| 9. Определить, является ли строка палиндромом                                      ||\n"
           "|| 10. Вывести стек                                                                   ||\n"
           "======================================Разное============================================\n"
           "|| 11. Анализ эффективности                                                           ||\n"
           "|| 0. Выход                                                                           ||\n"
           "========================================================================================\n");
}
void input_step_menu(int *step, int min, int max)
{
    int rc = -1;
    char buff[8];
    while(rc != EXIT_SUCCESS)
    {
        printf("\nВведите команду: ");
        if (scanf("%d", step) != 1)
            rc = INVALID_ERR;
        else if (*step > max || *step < min)
             rc = STEP_ERR;
        else
            rc = EXIT_SUCCESS;
        fgets(buff, sizeof(buff), stdin);
        print_error(rc);
    }
}

void print_measure_data(size_t size, int64_t time_array, int64_t time_list)
{
    printf("\n┌───────────────┬─────────────────┬────────────────┐\n"
           "│    Размер     │   Стек Массив   │    Стек Лист   │\n"
           "├───────────────┼─────────────────┼────────────────┤\n");
    printf("│ %-13zu │ %-15"PRId64" │ %-14"PRId64" │\n", size, time_array, time_list);
    printf("└───────────────┴─────────────────┴────────────────┘\n");
}
void print_size_data(size_t size, size_t size_array, size_t size_list)
{
    printf("\n┌───────────────┬─────────────────┬────────────────┐\n"
           "│    Размер     │   Стек Массив   │    Стек Лист   │\n"
           "├───────────────┼─────────────────┼────────────────┤\n");
    printf("│ %-13zu │ %-15zu │ %-14zu │\n", size, size_array, size_list);
    printf("└───────────────┴─────────────────┴────────────────┘\n");
}

void auto_measure_time()
{
    int size = -1;
    char buff[8];
    while (size <= 0)
    {
        printf("\nВведите размер для автозаполнения стэка: ");
        if(scanf("%d", &size) != 1)
            printf("Ошибка! Размер введен неправильно.\n");
        if (size < 0 || size >= SIZE_STACK)
            printf("Ошибка! Размер не может быть отрицательным.\n");
        fgets(buff, sizeof(buff), stdin);
    }

    struct timeval tv_start, tv_stop;
    int64_t time, elapsed_push_list = 0, elapsed_push_array = 0,
                  elapsed_pop_list = 0, elapsed_pop_array = 0,
                  elapsed_pal_list = 0, elapsed_pal_array = 0;
    stack_array_t stack_array;
    defaul_stack_array_t(&stack_array);

    stack_list_t *ptr_stack, stack_list;
    defaul_stack_list_t(&stack_list);
    ptr_stack = NULL;



    for (int j = 0; j < I_STEP; j++)
    {
        gettimeofday(&tv_start, NULL);
        stack_array.string = allocate_array_char(SIZE_STACK);
        gettimeofday(&tv_stop, NULL);
        time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        elapsed_pal_array += time;

        for (int i = 0; i < size; i++)
        {
            char symbol = (char) (97 + rand() % (122 - 97));

            gettimeofday(&tv_start, NULL);
            push_array(&stack_array, symbol);
            gettimeofday(&tv_stop, NULL);

            time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            elapsed_push_array += time;

            if (ptr_stack == NULL)
            {
                ptr_stack = &stack_list;
                gettimeofday(&tv_start, NULL);
                ptr_stack = symbol_create(symbol);
                gettimeofday(&tv_stop, NULL);
            }
            else
            {
                gettimeofday(&tv_start, NULL);
                push_stack_list_t(&ptr_stack, symbol);
                gettimeofday(&tv_stop, NULL);
            }
            time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            elapsed_push_list += time;
        }

        for (int i = 0; i < size; i++)
        {
            gettimeofday(&tv_start, NULL);
            pop_array(&stack_array);
            gettimeofday(&tv_stop, NULL);
            time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            elapsed_pop_array += time;

            gettimeofday(&tv_start, NULL);
            pop_stack_list(&ptr_stack);
            gettimeofday(&tv_stop, NULL);
            time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
            elapsed_pop_list += time;
        }

        free_stack_array(&stack_array);
        free_stack_list(&ptr_stack);
    }

    elapsed_push_array /= (I_STEP - 2);
    elapsed_pop_array /= (I_STEP - 2);
    elapsed_push_list /= (I_STEP - 2);
    elapsed_pop_list /= (I_STEP - 2);

    printf("\n Замеры времени операции добавления:");
    print_measure_data(size, elapsed_push_array, elapsed_push_list);

    printf("\n Замеры времени операции удаления:");
    print_measure_data(size, elapsed_pop_array, elapsed_pop_list);

    for (int j = 0; j < I_STEP; j++)
    {
        stack_array.string = allocate_array_char(SIZE_STACK);
        for (int i = 0; i < size; i++)
        {
            char symbol = (char) (97 + rand() % (122 - 97));

            push_array(&stack_array, symbol);
            if (ptr_stack == NULL)
            {
                ptr_stack = &stack_list;
                ptr_stack = symbol_create(symbol);
            }
            else
                push_stack_list_t(&ptr_stack, symbol);

        }

        gettimeofday(&tv_start, NULL);
        (void) stack_array_is_palindrom(&stack_array);
        gettimeofday(&tv_stop, NULL);
        time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        elapsed_pal_array += time;

        gettimeofday(&tv_start, NULL);
        (void) stack_list_is_palindrom(&ptr_stack);
        gettimeofday(&tv_stop, NULL);

        time = (tv_stop.tv_sec - tv_start.tv_sec) * 1000000LL + (tv_stop.tv_usec - tv_start.tv_usec);
        elapsed_pal_list += time;

        free_stack_array(&stack_array);
        free_stack_list(&ptr_stack);
    }
    elapsed_pal_list /= (I_STEP - 2);
    elapsed_pal_array /= (I_STEP - 2);

    printf("\n Замеры времени - Полиндром:");
    print_measure_data(size, elapsed_pal_array, elapsed_pal_list);

    printf("\n Замеры памяти:");
    print_size_data(size, (SIZE_STACK - 1) * sizeof(char) + sizeof(int),
    size * sizeof(stack_list_t));
}

int main()
{
    setbuf(stdout, NULL);

    stack_array_t stack_array;
    defaul_stack_array_t(&stack_array);

    stack_list_t *stack_list, stack;
    stack_list = NULL;
    defaul_stack_list_t(&stack);

    int rc = EXIT_SUCCESS;
    int step = -1;

    int flag_array = 0, flag_list = 0;
    print_conditions();
    print_menu();
    while (step != 0)
    {
        input_step_menu(&step, 0, 11);
        if (step == 0)
        {
            if (flag_array == 1)
                free_stack_array(&stack_array);
            if (flag_list == 1)
                free_stack_list(&stack_list);
            printf("До свидания!");
        }
        else if (step == 1)
        {
            if (stack_array.size > 0)
                printf("Cтэк уже создан. Чтобы добавить, удалить или проверить на полидромность пользуйтесь меню.\n");
            else
            {
                flag_array = 1;
                stack_array.string = allocate_array_char(SIZE_STACK);
                if (!stack_array.string)
                    rc = MEMORY_ERR;
                else
                    rc = input_stack_array(&stack_array);

                if (rc != EXIT_SUCCESS)
                {
                    if (rc == STACK_OVERFLOW)
                        free_stack_array(&stack_array);
                    print_error(rc);
                    rc = EXIT_SUCCESS;
                }
            }
        }
        else if (step == 2)
        {
            char symbol;
            char buff[8];
            printf("Введите символ для добавления в стэк: ");
            scanf("%c", &symbol);
            fgets(buff, sizeof(buff), stdin);
            if (flag_array == 0)
            {
                flag_array = 1;
                stack_array.string = allocate_array_char(SIZE_STACK);
                if (!stack_array.string)
                    rc = MEMORY_ERR;
            }
            if (rc == EXIT_SUCCESS)
                rc = push_array(&stack_array, symbol);
            if (rc != EXIT_SUCCESS)
            {
                print_error(rc);
                rc = EXIT_SUCCESS;
            }
        }
        else if (step == 3)
        {
            if (stack_array.size > 0) {
                pop_array(&stack_array);
                printf("Элемент удален.\n");
            } else
                print_error(EMPTY_STACK);
        }
        else if (step == 4)
        {
            if (stack_array.size > 0)
            {
                int result = stack_array_is_palindrom(&stack_array);
                if (result == POLINROM)
                    printf("Это полиндром.\n");
                else if (result == NO_POLIDROM)
                    printf("Это не полиндром.\n");
                else
                    printf("EE\n");
            } else
                print_error(EMPTY_STACK);
        }
        else if (step == 5)
        {
            rc = print_stack_array(&stack_array);
            print_error(rc);
            rc = EXIT_SUCCESS;
            print_menu();
        }
        else if (step == 6)
        {
            if (stack_list != NULL)
                printf("Cтэк уже создан. Чтобы добавить, удалить или проверить на полидромность пользуйтесь меню.\n");
            else
            {
                flag_list = 1;
                stack_list = &stack;
                rc = input_stack_list_t(&stack_list);
                if (rc == STACK_OVERFLOW)
                    free_stack_list(&stack_list);
                print_error(rc);
                rc = EXIT_SUCCESS;
            }

        }
        else if (step == 7)
        {
            char symbol;
            char buff[8];
            printf("Введите символ для добавления в стэк: ");
            scanf("%c", &symbol);
            fgets(buff, sizeof(buff), stdin);
            if (stack_list == NULL)
            {
                stack_list = &stack;
                stack_list = symbol_create(symbol);
                flag_list = 1;
            }
            else
                rc = push_stack_list_t(&stack_list, symbol);
            print_error(rc);
            rc = EXIT_SUCCESS;
        }
        else if (step == 8)
        {
            if (stack_list != NULL)
            {
                rc = pop_stack_list(&stack_list);
                print_error(rc);
                rc = EXIT_SUCCESS;
                printf("Элемент удален.\n");
            } else
                print_error(EMPTY_STACK);

        }
        else if (step == 9)
        {
            if (stack_list != NULL)
            {
                int result = stack_list_is_palindrom(&stack_list);
                if (result == POLINROM)
                    printf("Это полиндром.\n");
                else
                    printf("Это не полиндром.\n");
            } else
                print_error(EMPTY_STACK);
        }
        else if (step == 10)
        {
            rc = print_stack_list_t(stack_list);
            print_error(rc);
            rc = EXIT_SUCCESS;
            print_menu();
        }
        else if (step == 11)
            auto_measure_time();
    }
    return EXIT_SUCCESS;
}