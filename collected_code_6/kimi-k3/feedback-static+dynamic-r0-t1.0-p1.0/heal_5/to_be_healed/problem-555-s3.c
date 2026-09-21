#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>

int64_t calculate_difference(int n)
{
    int64_t sum_n = (int64_t)n * (n + 1) / 2;
    int64_t sum_cubes;

    if (sum_n != 0 && (sum_n > INT64_MAX / sum_n || sum_n < INT64_MIN / sum_n))
    {
        return -1;
    }

    sum_cubes = sum_n * sum_n;
    return sum_cubes - sum_n;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr;
    long input;
    int n;
    int64_t result;
    size_t len;

    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input\n");
        return EXIT_FAILURE;
    }

    len = 0;
    while (len < sizeof(buffer) && buffer[len] != '\0')
    {
        len++;
    }

    if (len == sizeof(buffer))
    {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    input = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Invalid input format\n");
        return EXIT_FAILURE;
    }

    if (input < 1 || input > 1299709)
    {
        fprintf(stderr, "Input out of valid range\n");
        return EXIT_FAILURE;
    }

    n = (int)input;
    result = calculate_difference(n);

    if (result < 0)
    {
        fprintf(stderr, "Calculation overflow\n");
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);

    return EXIT_SUCCESS;
}