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

    return (uintmax_t)(-(value + 1)) + UINTMAX_C(1);
}

static uintmax_t greatest_common_divisor(intmax_t first, intmax_t second)
{
    uintmax_t a = magnitude(first);
    uintmax_t b = magnitude(second);

    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int parse_intmax(const char **input, intmax_t *value)
{
    char *end;

    errno = 0;
    *value = strtoimax(*input, &end, 10);

    if (end == *input || errno == ERANGE) {
        return 0;
    }

    *input = end;
    return 1;
}

int main(void)
{
    char line[256];
    const char *cursor;
    intmax_t first;
    intmax_t second;

    if (fgets(line, sizeof line, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = line;

    if (!parse_intmax(&cursor, &first) ||
        !parse_intmax(&cursor, &second)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\n' || *cursor == '\r' ||
           *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", greatest_common_divisor(first, second));
    return EXIT_SUCCESS;
}