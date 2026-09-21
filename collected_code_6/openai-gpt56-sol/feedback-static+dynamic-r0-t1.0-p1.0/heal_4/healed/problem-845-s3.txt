#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

static int factorial_digit_count(unsigned long long n,
                                 unsigned long long *count)
{
    long double logarithm;
    long double value;
    long double divisor;

    if (count == NULL) {
        return -1;
    }

    if (n < 2ULL) {
        *count = 1ULL;
        return 0;
    }

    if ((long double)n > LDBL_MAX - 1.0L) {
        return -1;
    }

    errno = 0;
    logarithm = lgammal((long double)n + 1.0L);

    if (errno != 0 || !isfinite(logarithm)) {
        return -1;
    }

    divisor = logl(10.0L);
    if (!isfinite(divisor) || divisor <= 0.0L) {
        return -1;
    }

    value = logarithm / divisor;

    if (!isfinite(value) || value < 0.0L ||
        value >= (long double)ULLONG_MAX) {
        return -1;
    }

    *count = (unsigned long long)floorl(value) + 1ULL;
    return 0;
}

static int read_unsigned_long_long(unsigned long long *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *cursor;
    char *end;
    unsigned long long parsed;

    if (value == NULL) {
        return -1;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return -1;
    }

    cursor = line;
    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor == '-') {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtoull(cursor, &end, 10);

    if (errno == ERANGE || end == cursor) {
        free(line);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *value = parsed;
    free(line);
    return 0;
}

int main(void)
{
    unsigned long long n;
    unsigned long long digits;

    if (read_unsigned_long_long(&n) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (factorial_digit_count(n, &digits) != 0) {
        fputs("Unable to calculate digit count\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", digits) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}