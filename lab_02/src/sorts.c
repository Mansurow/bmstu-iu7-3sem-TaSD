#include "utils.h"
#include "sorts.h"

// сортировка простой пузырек
void buble_sort_key(st_key_travel *key, size_t n_key)
{
    st_key_travel buff;
    for (size_t i = 0; i < n_key; i++)
        for (size_t j = i; j < n_key - 1; j++)
            if (strcmp(key[j].name_country, key[j + 1].name_country) > 0)
            {
                buff = key[j];
                key[j] = key[j + 1];
                key[j + 1] = buff;
            }
}
void buble_sort_table(st_travel *countries, size_t n_countries)
{
    st_travel buff;
    for (size_t i = 0; i < n_countries; i++)
        for (size_t j = i; j < n_countries - 1; j++)
            if (strcmp(countries[j].main_data.name_country, countries[j + 1].main_data.name_country) > 0)
            {
                buff = countries[j];
                countries[j] = countries[j + 1];
                countries[j + 1] = buff;
            }
}
// пузырек с флажком
void buble_sort_flag_key(st_key_travel *key, size_t n_key)
{
    _Bool flag = true;
    st_key_travel buff;
    for (size_t i = 0; i < n_key; i++)
    {
        for (size_t j = i; j < n_key - 1; j++)
            if (strcmp(key[j].name_country, key[j + 1].name_country) > 0) {
                buff = key[j];
                key[j] = key[j + 1];
                key[j + 1] = buff;
                flag = false;
            }
        if (flag)
            break;
    }
}
void buble_sort_flag_table(st_travel *countries, size_t n_countries)
{
    st_travel buff;
    _Bool flag = true;
    for (size_t i = 0; i < n_countries; i++)
    {
        for (size_t j = i; j < n_countries - 1; j++)
            if (strcmp(countries[j].main_data.name_country, countries[j + 1].main_data.name_country) > 0)
            {
                buff = countries[j];
                countries[j] = countries[j + 1];
                countries[j + 1] = buff;
                flag = false;
            }
        if (flag)
            break;
    }
}
// сортировка простыми вставками
void insert_sort_table(st_travel *countries, size_t n_countries)
{
    for (size_t i = 1; i < n_countries; i++)
    {
        st_travel buff = countries[i];
        int j = i - 1;
        for (; j >= 0 && strcmp(countries[j].main_data.name_country, buff.main_data.name_country) > 0; j--)
            countries[j + 1] = countries[j];
        countries[j + 1] = buff;
    }
}
void insert_sort_key(st_key_travel *key, size_t n_key)
{
    for (size_t i = 1; i < n_key; i++)
    {
        st_key_travel buff = key[i];
        int j = i - 1;
        for (; j >= 0 && strcmp(key[j].name_country, buff.name_country) > 0; j--)
            key[j + 1] =key[j];
        key[j + 1] = buff;
    }
}
// сортировка бинарными вставками
void insert_sort_binary_table(st_travel *countries, size_t n_countries)
{
    for (size_t i = 1; i < n_countries; i++)
    {
        st_travel buff = countries[i];
        int lo = 0, hi = i;
        if (lo == hi)
            lo++;
        else
            while (lo < hi)
            {
                int mid = (lo + hi) / 2;
                if (strcmp(buff.main_data.name_country, countries[mid].main_data.name_country) < 0)
                    hi = mid;
                else
                    lo = mid + 1;
            }
        int j = i;
        while (j > lo && j > 0) {
            countries[j] = countries[j - 1];
            j--;
        }
        countries[lo] = buff;
    }
}
void insert_sort_binary_key(st_key_travel *key, size_t n_key)
{
    for (size_t i = 1; i < n_key; i++)
    {
        st_key_travel buff = key[i];
        int lo = 0, hi = i;
        if (lo == hi)
            lo++;
        else
            while (lo < hi)
            {
                int mid = (lo + hi) / 2;
                if (strcmp(buff.name_country, key[mid].name_country) < 0)
                    hi = mid;
                else
                    lo = mid + 1;
            }
        int j = i;
        while (j > lo && j > 0) {
            key[j] = key[j - 1];
            j--;
        }
        key[lo] = buff;
    }
}
// сортировка шелла
void shell_sort_table(st_travel *countries, size_t n_countries)
{
    int i, j, step;
    st_travel buff;
    for (step = n_countries / 2; step > 0; step /= 2)
        for (i = step; i < n_countries; i++)
        {
            buff = countries[i];
            for (j = i; j >= step; j -= step)
            {
                if (strcmp(buff.main_data.name_country, countries[j - step].main_data.name_country) < 0)
                    countries[j] = countries[j - step];
                else
                    break;
            }
            countries[j] = buff;
        }
}
void shell_sort_key(st_key_travel *key, size_t n_key)
{
    int i, j, step;
    st_key_travel buff;
    for (step = n_key / 2; step > 0; step /= 2)
        for (i = step; i < n_key; i++)
        {
            buff = key[i];
            for (j = i; j >= step; j -= step)
            {
                if (strcmp(buff.name_country, key[j - step].name_country) < 0)
                    key[j] = key[j - step];
                else
                    break;
            }
            key[j] = buff;
        }
}
// быстрая сортировка
void qiuck_sort_table(st_travel *countries, size_t left, size_t right)
{
    int l_hold = left, r_hold = right;
    st_travel buff = countries[left];
    while (left < right)
    {
        while (strcmp(countries[right].main_data.name_country, buff.main_data.name_country) >= 0
               && (left < right))
            right--; // сдвиг правой границы пока rignt больше buff
        if (left != right) // если границы не сомкнулись
        {
            countries[left] = countries[right];
            left++; // сдвигаем левую границу вправо
        }
        while (strcmp(countries[left].main_data.name_country, buff.main_data.name_country) <= 0
               && (left < right))
            left++;
        if (left != right) // если границы не сомкнулись
        {
            countries[right] = countries[left];
            right--; // сдвигаем правую границу влево
        }
    }
    countries[left] = buff;
    int pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        qiuck_sort_table(countries, left, pivot - 1);
    if (right > pivot)
        qiuck_sort_table(countries, pivot + 1, right);
}
void qiuck_sort_key(st_key_travel *key, size_t left, size_t right)
{
    int l_hold = left, r_hold = right;
    st_key_travel buff = key[left];
    while (left < right)
    {
        while (strcmp(key[right].name_country, buff.name_country) >= 0
               && (left < right))
            right--; // сдвиг правой границы пока rignt больше buff
        if (left != right) // если границы не сомкнулись
        {
            key[left] = key[right];
            left++; // сдвигаем левую границу вправо
        }
        while (strcmp(key[left].name_country, buff.name_country) <= 0
               && (left < right))
            left++;
        if (left != right) // если границы не сомкнулись
        {
            key[right] = key[left];
            right--; // сдвигаем правую границу влево
        }
    }
    key[left] = buff;
    int pivot = left;
    left = l_hold;
    right = r_hold;
    if (left < pivot)
        qiuck_sort_key(key, left, pivot - 1);
    if (right > pivot)
        qiuck_sort_key(key, pivot + 1, right);
}