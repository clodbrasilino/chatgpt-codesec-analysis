#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <math.h>

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

    long long max_n = (long long)sqrt((double)LLONG_MAX);

    if (n > max_n)
    {
        n = (int)max_n;
    }

    for (i = 1; i <= n; i++)
    {
        if (sum > LLONG_MAX - i)
        {
            break;
        }
        sum += i;

        if (sum_of_squares > LLONG_MAX - (long long)i * i)
        {
            break;
        }
        sum_of_squares += (long long)i * i;
    }

    if (sum > (long long)sqrt((double)LLONG_MAX))
    {
        square_of_sum = LLONG_MAX;
    }
    else
    {
        square_of_sum = sum * sum;
    }

    if (square_of_sum == LLONG_MAX || sum_of_squares > LLONG_MAX - square_of_sum)
    {
        difference = LLONG_MAX;
    }
    else
    {
        difference = square_of_sum - sum_of_squares;
    }

    return difference;
}

int main(void)
{
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

    n = (int)parsed_value;

    result = calculate_difference(n);

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}