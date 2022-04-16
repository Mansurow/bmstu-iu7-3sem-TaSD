#include "../inc/math_func.h"

double rand_double(double min, double max)
{
    return (max - min) * ((double) rand() / (double) RAND_MAX) + min;
}

int cmp_double(double a, double b)
{
    if (fabs(a - b) <= EPS)
        return 0;
    else if (a < (b - EPS))
        return -1;
    else
        return 1;
}