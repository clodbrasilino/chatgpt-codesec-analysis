#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <ctype.h>

long long calculate_difference(int n)
{
    long long sum = 0;
    long long sum_of_squares = 0;
    long long square_of_sum;
    long long difference;
    int i;

    if (n <= 0)
    {
        return 0;
    }

    for (i = 1; i <= n; i++)
    {
        if (sum > LLONG_MAX - i)
        {
            return -1;
        }
        sum += i;

        if (i != 0 && (long long)i > LLONG_MAX / i)
        {
            return -1;
        }
        if (sum_of_squares > LLONG_MAX - (long long)i * i)
        {
            return -1;
        }
        sum_of_squares += (long long)i * i;
    }

    if (sum != 0 && llabs(sum) > LLONG_MAX / llabs(sum))
    {
        return -1;
    }
    square_of_sum = sum * sum;

    if (square_of_sum < sum_of_squares)
    {
        return -1;
    }
    difference = square_of_sum - sum_of_squares;

    return difference;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input_buffer[256];
    char *end_pointer;
    long parsed_value;
    int n;
    long long result;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_value = strtol(input_buffer, &end_pointer, 10);

    if (errno == ERANGE || parsed_value > INT_MAX || parsed_value < 0)
    {
        fprintf(stderr, "Error: Input out of valid range.\n");
        return EXIT_FAILURE;
    }

    if (end_pointer == input_buffer)
    {
        fprintf(stderr, "Error: No digits found in input.\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end_pointer))
    {
        end_pointer++;
    }

    if (*end_pointer != '\0')
    {
        fprintf(stderr, "Error: Invalid characters in input.\n");
        return EXIT_FAILURE;
    }

    n = (int)parsed_value;

    result = calculate_difference(n);

    if (result == -1)
    {
        fprintf(stderr, "Error: Integer overflow occurred.\n");
        return EXIT_FAILURE;
    }

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}