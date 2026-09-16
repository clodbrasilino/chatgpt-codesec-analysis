#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int add_in_range(int a, int b, int low, int high, int *result);

int add_in_range(int a, int b, int low, int high, int *result)
{
    long long sum;

    if (result == NULL)
    {
        return -1;
    }

    sum = (long long)a + (long long)b;

    if (sum > INT_MAX || sum < INT_MIN)
    {
        return -1;
    }

    if (sum >= (long long)low && sum <= (long long)high)
    {
        *result = 20;
    }
    else
    {
        *result = (int)sum;
    }

    return 0;
}

int main(void)
{
    int result = 0;
    int status;

    status = add_in_range(5, 7, 10, 20, &result);
    if (status != 0)
    {
        fprintf(stderr, "Error: addition failed or overflowed\n");
        return EXIT_FAILURE;
    }
    printf("Result: %d\n", result);

    status = add_in_range(100, 200, 10, 20, &result);
    if (status != 0)
    {
        fprintf(stderr, "Error: addition failed or overflowed\n");
        return EXIT_FAILURE;
    }
    printf("Result: %d\n", result);

    status = add_in_range(INT_MAX, 1, 10, 20, &result);
    if (status != 0)
    {
        fprintf(stderr, "Error: addition failed or overflowed\n");
    }
    else
    {
        printf("Result: %d\n", result);
    }

    return EXIT_SUCCESS;
}