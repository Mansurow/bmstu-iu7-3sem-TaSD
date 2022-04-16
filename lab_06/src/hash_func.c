#include "../inc/hash_struct.h"

int hash_func(int num, int divide)
{
    return abs(num % divide);
}

int select_prime(int max)
{
    int prime_nums[20] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71 };
    for (int i = 0; i < 20; i++)
    {
        if (prime_nums[i] > max)
        {
            //printf("prime is %d", prime_nums[i]);
            return prime_nums[i];
        }
    }
    return max + 1;
}
