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
    long double argument;
    long double base10;

    if (count == NULL) {
        return -1;
    }

    if (n < 2ULL) {
        *count = 1ULL;
        return 0;
    }

    argument = (long double)n + 1.0L;
    if (!isfinite(argument) || argument <= (long double)n) {
        return -1;
    }

    errno = 0;
    base10 = logl(10.0L);
    logarithm = lgammal(argument) / base10;

    if (errno != 0 || !isfinite(base10) || base10 <= 0.0L ||
        !isfinite(logarithm) || logarithm < 0.0L ||
        logarithm >= (long double)ULLONG_MAX) {
        return -1;
    }

    *count = (unsigned long long)floorl(logarithm) + 1ULL;
    return 0;
}

static int read_number(unsigned long long *value)
{
    char *line = NULL;
    size_t capacity = 0U;
    size_t length = 0U;
    char *start;
    char *end;
    unsigned long long result;
    int ch;
    int status = -1;

    if (value == NULL) {
        return -1;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *new_line;
        size_t new_capacity;

        if (length == SIZE_MAX - 1U) {
            goto cleanup;
        }

        if (length + 1U >= capacity) {
            if (capacity == 0U) {
                new_capacity = 64U;
            } else {
                if (capacity > SIZE_MAX / 2U) {
                    goto cleanup;
                }
                new_capacity = capacity * 2U;
            }

            new_line = realloc(line, new_capacity);
            if (new_line == NULL) {
                goto cleanup;
            }

            line = new_line;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && ferror(stdin)) {
        goto cleanup;
    }

    if (length == 0U && ch == EOF) {
        goto cleanup;
    }

    if (length + 1U > capacity) {
        char *new_line = realloc(line, length + 1U);

        if (new_line == NULL) {
            goto cleanup;
        }

        line = new_line;
        capacity = length + 1U;
    }

    line[length] = '\0';
    start = line;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        goto cleanup;
    }

    errno = 0;
    result = strtoull(start, &end, 10);

    if (errno == ERANGE || end == start) {
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        goto cleanup;
    }

    *value = result;
    status = 0;

cleanup:
    free(line);
    return status;
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