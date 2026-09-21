#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int factorial_digit_count(unsigned long long n,
                                  unsigned long long *count)
{
    long double logarithm;
    long double value;

    if (count == NULL) {
        return -1;
    }

    if (n < 2ULL) {
        *count = 1ULL;
        return 0;
    }

    value = (long double)n + 1.0L;
    if (!isfinite(value) || value <= (long double)n) {
        return -1;
    }

    errno = 0;
    logarithm = lgammal(value) / logl(10.0L);

    if (errno != 0 || !isfinite(logarithm) || logarithm < 0.0L ||
        logarithm >= (long double)ULLONG_MAX) {
        return -1;
    }

    *count = (unsigned long long)floorl(logarithm) + 1ULL;
    return 0;
}

static int read_number(unsigned long long *value)
{
    char buffer[128];
    char *start;
    char *parse_end;
    unsigned long long result;
    size_t length;
    int ch;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (buffer[length] != '\0') {
        return -1;
    } else {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return -1;
        }

        if (ch == EOF && ferror(stdin)) {
            return -1;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        return -1;
    }

    errno = 0;
    result = strtoull(start, &parse_end, 10);

    if (errno == ERANGE || parse_end == start) {
        return -1;
    }

    while (isspace((unsigned char)*parse_end)) {
        ++parse_end;
    }

    if (*parse_end != '\0') {
        return -1;
    }

    *value = result;
    return 0;
}

int main(void)
{
    unsigned long long n;
    unsigned long long digits;

    if (read_number(&n) != 0) {
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