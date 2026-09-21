#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

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
        sum += i;
        sum_of_squares += (long long)i * i;
    }

    square_of_sum = sum * sum;
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
    int has_newline;

    if (fgets(input_buffer, sizeof(input_buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error: Failed to read input.\n");
        return EXIT_FAILURE;
    }

    has_newline = 0;
    for (size_t i = 0; i < sizeof(input_buffer); i++)
    {
        if (input_buffer[i] == '\n')
        {
            has_newline = 1;
            input_buffer[i] = '\0';
            break;
        }
        if (input_buffer[i] == '\0')
        {
            break;
        }
    }

    if (!has_newline && !feof(stdin))
    {
        int ch;
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
        }
        fprintf(stderr, "Error: Input too long.\n");
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

    if (*end_pointer != '\0')
    {
        fprintf(stderr, "Error: Invalid characters in input.\n");
        return EXIT_FAILURE;
    }

    n = (int)parsed_value;

    result = calculate_difference(n);

    printf("%lld\n", result);

    return EXIT_SUCCESS;
}