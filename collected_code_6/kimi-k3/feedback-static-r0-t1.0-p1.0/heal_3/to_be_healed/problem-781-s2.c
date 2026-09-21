#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

int is_divisor_count_odd(unsigned long long n)
{
    if (n == 0)
    {
        return -1;
    }
    unsigned long long i = 1;
    while (i <= n / i)
    {
        i++;
    }
    return ((i - 1) * (i - 1) == n) ? 1 : 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *endptr;
    unsigned long long value;
    int result;
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
        fprintf(stderr, "Input too long\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(buffer, &endptr, 10);

    if (errno == ERANGE)
    {
        fprintf(stderr, "Input out of range\n");
        return EXIT_FAILURE;
    }

    if (endptr == buffer || (*endptr != '\n' && *endptr != '\0'))
    {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (value == 0)
    {
        fprintf(stderr, "Zero has infinitely many divisors\n");
        return EXIT_FAILURE;
    }

    result = is_divisor_count_odd(value);

    if (result < 0)
    {
        fprintf(stderr, "Computation error\n");
        return EXIT_FAILURE;
    }

    printf("%s\n", result ? "Odd" : "Even");

    return EXIT_SUCCESS;
}