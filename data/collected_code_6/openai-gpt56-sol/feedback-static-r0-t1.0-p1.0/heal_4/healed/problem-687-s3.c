#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0
        ? (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1)
        : (uintmax_t)value;
}

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_intmax(intmax_t *value)
{
    char token[128];
    size_t length = 0;
    int ch;

    do {
        ch = getchar();
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    do {
        if (length + 1 >= sizeof token) {
            while ((ch = getchar()) != EOF &&
                   !isspace((unsigned char)ch)) {
            }
            return 0;
        }

        token[length++] = (char)ch;
        ch = getchar();
    } while (ch != EOF && !isspace((unsigned char)ch));

    token[length] = '\0';

    errno = 0;
    char *end;
    intmax_t parsed = strtoimax(token, &end, 10);

    if (errno == ERANGE || end == token || *end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int only_whitespace_remains(void)
{
    int ch;

    while ((ch = getchar()) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return !ferror(stdin);
}

int main(void)
{
    intmax_t first;
    intmax_t second;

    if (!read_intmax(&first) ||
        !read_intmax(&second) ||
        !only_whitespace_remains()) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n",
           gcd(magnitude(first), magnitude(second)));

    return EXIT_SUCCESS;
}