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

static int read_number(unsigned long long *value)
{
    char *line = NULL;
    size_t capacity = 0U;
    ssize_t length;
    char *start;
    char *end;
    unsigned long long parsed;
    int valid = 0;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    while (length > 0 &&
           (line[length - 1] == '\n' || line[length - 1] == '\r')) {
        line[--length] = '\0';
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoull(start, &end, 10);

    if (errno != ERANGE && end != start && parsed != 0ULL) {
        while (isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end == '\0') {
            *value = parsed;
            valid = 1;
        }
    }

    free(line);
    return valid;
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