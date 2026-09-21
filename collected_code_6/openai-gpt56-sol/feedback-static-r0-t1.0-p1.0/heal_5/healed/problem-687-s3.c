#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value >= 0) {
        return (uintmax_t)value;
    }

    return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
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

    if (value == NULL) {
        return 0;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && !isspace((unsigned char)ch)) {
        if (length >= sizeof token - 1) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));

            return 0;
        }

        token[length++] = (char)ch;
        ch = fgetc(stdin);
    }

    if (ferror(stdin)) {
        return 0;
    }

    token[length] = '\0';

    errno = 0;
    char *end = NULL;
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

    while ((ch = fgetc(stdin)) != EOF) {
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

    if (printf("%" PRIuMAX "\n",
               gcd(magnitude(first), magnitude(second))) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}