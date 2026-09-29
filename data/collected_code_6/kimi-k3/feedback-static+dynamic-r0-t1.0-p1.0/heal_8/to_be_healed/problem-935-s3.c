#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

unsigned long long sum_of_squares(int n)
{
    unsigned long long un = (unsigned long long)n;
    return un * (un + 1) * (2 * un + 1) / 6ULL;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *endptr = NULL;
    long value;
    int n;

    printf("Enter a positive integer n: ");

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Input error.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtol(buffer, &endptr, 10);

    if (errno != 0 || endptr == buffer || (*endptr != '\n' && *endptr != '\0')) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (value < 1 || value > INT_MAX) {
        fprintf(stderr, "Input out of range.\n");
        return EXIT_FAILURE;
    }

    n = (int)value;

    if (n > 55108) {
        fprintf(stderr, "Input too large; result would overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Sum of squares = %llu\n", sum_of_squares(n));

    return EXIT_SUCCESS;
}