#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    return value < 0
        ? (uintmax_t)(-(value + 1)) + UINTMAX_C(1)
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

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;

    if (getline(&line, &capacity, stdin) < 0) {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    cursor = line;
    errno = 0;
    first = strtoimax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    second = strtoimax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        free(line);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n",
           gcd(magnitude(first), magnitude(second)));

    free(line);
    return EXIT_SUCCESS;
}