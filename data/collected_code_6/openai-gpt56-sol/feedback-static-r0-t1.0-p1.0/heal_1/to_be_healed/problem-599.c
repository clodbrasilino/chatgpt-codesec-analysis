#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    if (sum == NULL || average == NULL || n == 0) {
        return -1;
    }

    if ((n % 2 == 0 && n / 2 > ULLONG_MAX / (n + 1)) ||
        (n % 2 != 0 && n > ULLONG_MAX / ((n + 1) / 2))) {
        return -1;
    }

    *sum = (n % 2 == 0)
               ? (n / 2) * (n + 1)
               : n * ((n + 1) / 2);
    *average = (long double)(n + 1) / 2.0L;

    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end = NULL;
    unsigned long long n;
    unsigned long long sum;
    long double average;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    n = strtoull(input, &end, 10);

    if (errno == ERANGE || end == input || n == 0) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        return EXIT_FAILURE;
    }

    if (calculate_sum_and_average(n, &sum, &average) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}