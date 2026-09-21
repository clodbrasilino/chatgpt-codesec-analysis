#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int factorial_digit_count(unsigned long long n,
                                 unsigned long long *count)
{
    long double logarithm;

    if (count == NULL) {
        return -1;
    }

    if (n < 2ULL) {
        *count = 1ULL;
        return 0;
    }

    errno = 0;
    logarithm = lgammal((long double)n + 1.0L) / logl(10.0L);

    if (errno != 0 || !isfinite(logarithm) || logarithm < 0.0L ||
        logarithm >= (long double)ULLONG_MAX) {
        return -1;
    }

    *count = (unsigned long long)floorl(logarithm) + 1ULL;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    unsigned long long number;
    unsigned long long digits;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Input error\n", stderr);
        return EXIT_FAILURE;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    number = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (factorial_digit_count(number, &digits) != 0) {
        fputs("Calculation error\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", digits) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}