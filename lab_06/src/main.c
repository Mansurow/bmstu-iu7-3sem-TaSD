#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../inc/menu.h"
#include "../inc/tree_struct.h"
#include "../inc/hash_struct.h"
#include "../inc/measure.h"

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    int rc = EXIT_SUCCESS;

    if (argc == 2)
    {
        FILE *f_in = fopen(argv[1], "r");
        if (f_in == NULL)
        {
            rc = FILE_NOT_FOUND;
            fclose(f_in);
        }
        else if (check_file(f_in))
        {
            printf("ФАЙЛ пуст!\n");
            rc = FILE_IS_EMPTY;
        }
        else {
            int step = -1;

             tree_t tree;
             tree.head = NULL;

             hash_table_t hash;
             hash.size = 0;
             hash.divider = 0;
             hash.array = NULL;
             hash.elements = 0;
             hash.total_compare = 0;

             _Bool _is_read_tree = false, _is_balance = false, _is_push = false,
                   _is_read_hash = false;

             while (step != 0 && rc != MEMORY_ERR) {
                 print_menu();
                 input_step_menu(&step, 0, 12);
                 if (step == 0)
                 {
                     free(hash.array);
                     free_tree(&tree);
                     printf("До свидания!");
                 }
                 else if (step == 1)
                 {
                     if (!_is_read_tree) {
                         f_in =  fopen(argv[1], "r");
                         rc = fread_tree(f_in, &tree, false);
                         if (rc == INVALID_ERR) {
                             printf("В файле соддержатся сторонние символы!\n");
                             free_tree(&tree);
                         } else {
                             printf("Успешно прочитано!\n");
                             _is_read_tree = true;
                         }
                         fclose(f_in);
                     } else
                         printf("Данные уже прочитаны!\n");
                 }
                 else if (step == 2)
                 {
                     if (_is_read_tree || _is_push)
                     {
                         f_in = fopen(argv[1], "r");
                         free_tree(&tree);
                         rewind(f_in);
                         fread_tree(f_in, &tree, true);
                         _is_balance = true;
                         fclose(f_in);
                     } else
                         printf("Дерево пусто!\n");
                 }
                 else if (step == 3)
                 {
                     int number;
                     input_number(&number);
                     rc = push_tree(&tree.head, number, _is_balance);
                     if (rc == EXIT_SUCCESS) {
                         if (!_is_push)
                             _is_push = true;
                         printf("Элемент успешно добавлен!\n");
                     } else
                         printf("Элемент не добавлен!\n");
                 }
                 else if (step == 4)
                 {
                     if (_is_read_tree || _is_push)
                     {
                         int number, result;
                         input_number(&number);
                         result = search_element(tree.head, number);
                         if (result <= 0)
                             printf("Такого элемента нет в дереве!\n");
                         else
                         {
                             tree.head = pop_branch_tree(tree.head, number, _is_balance);
                             printf("Элемент успешно удален!\n");
                         }
                     } else
                         printf("Дерево пусто!\n");
                 }
                 else if (step == 5)
                 {
                     if (_is_read_tree || _is_push)
                     {
                         int count, number;
                         input_number(&number);
                         count = search_element(tree.head, number);
                         printf("Число \"%d\" %s в дереве, с %d количесвом сравнений\n", number,
                                 count > 0 ? "найдено" : "не найдено", abs(count));
                     } else
                         printf("Дерево пусто!\n");
                 }
                 else if (step == 6) {
                     if (_is_read_tree || _is_push) {
                         if (tree.head->height > 0)
                             print_tree(tree);
                         else
                             printf("В дереве один элемент - это %d(%d)\n", tree.head->number, tree.head->height);
                     } else printf("Дерево пусто!\n");
                 }
                 else if (step == 7)
                 {
                     if (!_is_read_hash) {
                         f_in = fopen(argv[1], "r");
                         rc = fread_hash(f_in, &hash);
                         if (rc == INVALID_ERR) {
                             printf("В файле соддержатся сторонние символы!\n");
                             free_tree(&tree);
                         } else {
                             printf("Успешно прочитано!\n");
                             _is_read_hash = true;
                         }
                     } else
                        printf("Даные прочитаны в hash!\n");
                 }
                 else if (step == 8) {
                     int number, in_cmp;
                     input_number(&number);
                     rc = push_hash(&hash, number);
                     if (rc == EXIT_SUCCESS) {
                         printf("Элемент успешно добавлен!\n");
                         printf("\n Введите макс. значение сравнений в хэш-таблице.\n");
                         input_number(&in_cmp);
                         if (in_cmp < hash.compare)
                         {
                             printf("Сравнений в хэштблице %d > %d при добавлении элемента %d\n", hash.compare, in_cmp, number);
                             hash_table_t rest_hash;
                             rest_hash.total_compare = 0;

                             print_hash(&hash);

                             rest_hash = restruct(hash, number, in_cmp);
                             printf("Сравнений в хэштблице(реструктуризация) %d <= %d при добавлении элемента %d\n", rest_hash.compare, in_cmp, number);

                             print_hash(&rest_hash);
                             free(rest_hash.array);
                         } else
                             printf("Сравнений в хэштблице %d <= %d при добавлении элемента %d\n", hash.compare, in_cmp, number);
                     } else
                         printf("Элемент не добавлен!\n");
                 }
                 else if (step == 9)
                 {
                     if (hash.array != NULL)
                     {
                         int number, in_cmp;
                         input_number(&number);
                         rc = pop_hash(&hash, number);
                         if (rc == ITEM_DELETE) {
                             printf("Элемент удален!\n");
                             printf("\n Введите макс. значение сравнений в хэш-таблице.\n");
                             input_number(&in_cmp);
                             if (in_cmp < hash.compare)
                             {
                                 printf("Сравнений в хэштблице %d > %d при добавлении элемента %d\n", hash.compare, in_cmp, number);
                                 hash_table_t rest_hash;
                                 rest_hash.total_compare = 0;

                                 print_hash(&hash);

                                 rest_hash = restruct(hash, number, in_cmp);
                                 printf("Сравнений в хэштблице(реструктуризация) %d <= %d при добавлении элемента %d\n", rest_hash.compare, in_cmp, number);

                                 print_hash(&rest_hash);
                                 free(rest_hash.array);
                             } else
                                 printf("Сравнений в хэштблице %d <= %d при добавлении элемента %d\n", hash.compare, in_cmp, number);

                         }
                         else
                             printf("Такого элемента нет в хэш-таблице!\n");
                     }
                     else
                         printf("Хэш-таблица пуста!\n");
                 }
                 else if (step == 10)
                 {
                     if (hash.array != NULL)
                     {
                         int number;
                         input_number(&number);
                         hash.compare = search_hash(&hash, number);
                         printf("Число \"%d\" %s в hash, с %d количесвом сравнений\n", number,
                                hash.compare > 0 ? "найдено" : "не найдено", hash.compare);
                     }
                     else
                         printf("Хэш-таблица пуста!\n");
                 }
                 else if (step == 11){
                     print_hash(&hash);
                 }
                 else if (step == 12)
                 {
                     auto_measure();
                 }
             }
        }
    } else
        rc = ARGV_ERR;

    return rc;
}