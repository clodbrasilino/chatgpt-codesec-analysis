#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned long long sum_of_cubes(int n)
{
    if (n <= 0)
    {
        return 0;
    }

    unsigned long long sum = 0;

    for (int i = 1; i <= n; i++)
    {
        unsigned long long cube = (unsigned long long)i * i * i;
        if (sum > ULLONG_MAX - cube)
        {
            return 0;
        }
        sum += cube;
    }

    return sum;
}

int main(int argc, char const * const * argv)
{
    int n;

    if (argc != 2)
    {
        return 1;
    }

    char *endptr;
    long val = strtol(argv[1], &endptr, 10);

    if (*endptr != '\0' || val < 0 || val > INT_MAX)
    {
        return 1;
    }

    n = (int)val;

    unsigned long long result = sum_of_cubes(n);

    if (result == 0 && n > 0)
    {
        return 1;
    }

    printf("%llu\n", result);

    return 0;
}