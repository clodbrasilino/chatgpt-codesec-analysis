#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

static bool multiply_overflow_ll(long long a, long long b, long long *result)
{
    if (a > 0 && b > 0 && a > LLONG_MAX / b)
    {
        return true;
    }
    *result = a * b;
    return false;
}

static bool add_overflow_ll(long long a, long long b, long long *result)
{
    if (b > 0 && a > LLONG_MAX - b)
    {
        return true;
    }
    *result = a + b;
    return false;
}

long long sum_of_fourth_powers(int n)
{
    long long sum = 0;
    int i;
    /* Possible weaknesses found:
     *  The scope of the variable 'i_ll' can be reduced. [variableScope]
     */
    long long i_ll, i2, i3, i4, new_sum;

    if (n < 0)
    {
        return -1;
    }

    for (i = 1; i <= n; i++)
    {
        i_ll = (long long)i;
        
        if (multiply_overflow_ll(i_ll, i_ll, &i2))
        {
            return -1;
        }
        
        if (multiply_overflow_ll(i2, i_ll, &i3))
        {
            return -1;
        }
        
        if (multiply_overflow_ll(i3, i_ll, &i4))
        {
            return -1;
        }
        
        if (add_overflow_ll(sum, i4, &new_sum))
        {
            return -1;
        }
        
        sum = new_sum;
    }

    return sum;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
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