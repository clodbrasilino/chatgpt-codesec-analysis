#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>
#include <ctype.h>

static int calculate_sum_and_average(unsigned long long n,
                                     unsigned long long *sum,
                                     long double *average)
{
    unsigned long long a;
    unsigned long long b;

    if (sum == NULL || average == NULL || n == 0ULL || n == ULLONG_MAX) {
        return 0;
    }

    a = n;
    b = n + 1ULL;

    if ((a & 1ULL) == 0ULL) {
        a /= 2ULL;
    } else {
        b /= 2ULL;
    }

    if (a != 0ULL && b > ULLONG_MAX / a) {
        return 0;
    }

    *sum = a * b;
    *average = (long double)(n + 1ULL) / 2.0L;

    return 1;
}

static int discard_line(void)
{
    int ch;

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static int read_number(unsigned long long *value)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *start;
    char *end;
    unsigned long long parsed;
    size_t length;

    if (value == NULL) {
        return 0;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    for (length = 0U; length < sizeof input && input[length] != '\0';
         ++length) {
        if (input[length] == '\n') {
            input[length] = '\0';
            break;
        }
    }

    if (length == sizeof input) {
        return 0;
    }

    if (input[length] == '\0' && length == sizeof input - 1U) {
        if (!discard_line()) {
            return 0;
        }
        return 0;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start || parsed == 0ULL) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    unsigned long long n;
    unsigned long long sum;
    long double average;

    if (!read_number(&n)) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_sum_and_average(n, &sum, &average)) {
        fputs("The result is outside the supported range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Sum: %llu\nAverage: %.2Lf\n", sum, average) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}