#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long long magnitude(long long value)
{
    if (value >= 0) {
        return (unsigned long long)value;
    }

    return 0ULL - (unsigned long long)value;
}

static unsigned long long minimum_operations(long long first, long long second)
{
    unsigned long long difference;

    if (first >= second) {
        return (unsigned long long)first - (unsigned long long)second;
    }

    difference = (unsigned long long)second - (unsigned long long)first;

    if (first > 0) {
        return 1ULL + difference / 2ULL;
    }

    return magnitude(first) + 1ULL + (unsigned long long)second / 2ULL;
}

static int read_long_long(long long *value)
{
    int ch;
    int sign = 1;
    unsigned long long result = 0;
    unsigned long long limit;

    do {
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\n' ||
             ch == '\r' || ch == '\f' || ch == '\v');

    if (ch == EOF) {
        return 0;
    }

    if (ch == '+' || ch == '-') {
        if (ch == '-') {
            sign = -1;
        }
        ch = getchar();
    }

    if (ch < '0' || ch > '9') {
        return 0;
    }

    limit = sign < 0
                ? (unsigned long long)LLONG_MAX + 1ULL
                : (unsigned long long)LLONG_MAX;

    do {
        unsigned int digit = (unsigned int)(ch - '0');

        if (result > (limit - digit) / 10ULL) {
            return 0;
        }

        result = result * 10ULL + digit;
        ch = getchar();
    } while (ch >= '0' && ch <= '9');

    if (ch != EOF) {
        if (ungetc(ch, stdin) == EOF) {
            return 0;
        }
    }

    if (sign < 0) {
        if (result == (unsigned long long)LLONG_MAX + 1ULL) {
            *value = LLONG_MIN;
        } else {
            *value = -(long long)result;
        }
    } else {
        *value = (long long)result;
    }

    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    while ((ch = getchar()) != EOF) {
        if (ch != ' ' && ch != '\t' && ch != '\n' &&
            ch != '\r' && ch != '\f' && ch != '\v') {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    long long first;
    long long second;

    errno = 0;

    if (!read_long_long(&first) ||
        !read_long_long(&second) ||
        !only_whitespace_remains()) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", minimum_operations(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}