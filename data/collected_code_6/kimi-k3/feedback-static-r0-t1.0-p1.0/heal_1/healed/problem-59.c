#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

int octagonal_number(int n, long long *result)
{
    if (result == NULL)
    {
        return -1;
    }

    if (n < 1)
    {
        return -1;
    }

    if (n > (LLONG_MAX + 2LL) / 3LL)
    {
        return -1;
    }

    long long factor = 3LL * n - 2LL;

    if ((long long)n > LLONG_MAX / factor)
    {
        return -1;
    }

    *result = (long long)n * factor;
    return 0;
}

int main(void)
{
    int n;
    long long result;

    printf("Enter the value of n: ");

    if (scanf("%d", &n) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (octagonal_number(n, &result) != 0)
    {
        fprintf(stderr, "Invalid input or overflow occurred\n");
        return EXIT_FAILURE;
    }

    printf("The %dth octagonal number is: %lld\n", n, result);

    return EXIT_SUCCESS;
}