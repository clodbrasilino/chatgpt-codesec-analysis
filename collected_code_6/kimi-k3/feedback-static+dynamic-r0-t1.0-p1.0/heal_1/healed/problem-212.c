#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long sum_of_fourth_powers(int n)
{
    long long sum = 0;
    int i;

    if (n < 0)
    {
        return -1;
    }

    for (i = 1; i <= n; i++)
    {
        long long i2 = (long long)i * i;
        long long i4 = i2 * i2;

        if (i2 == 0 || i4 / i2 != i2 || i4 > LLONG_MAX - sum)
        {
            return -1;
        }

        sum += i4;
    }

    return sum;
}

int main(void)
{
    char input[32];
    char *endptr;
    long value;
    int n;
    long long result;

    if (fgets(input, sizeof(input), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(input, &endptr, 10);

    if (errno == ERANGE || value > INT_MAX || value < 0)
    {
        fprintf(stderr, "Error: Invalid input range\n");
        return EXIT_FAILURE;
    }

    if (endptr == input || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Error: Invalid input format\n");
        return EXIT_FAILURE;
    }

    n = (int)value;
    result = sum_of_fourth_powers(n);

    if (result < 0)
    {
        fprintf(stderr, "Error: Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}