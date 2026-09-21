#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_even_parity(uint64_t value)
{
    bool parity = false;

    while (value != UINT64_C(0)) {
        parity = !parity;
        value &= value - UINT64_C(1);
    }

    return !parity;
}

int main(void)
{
    char *line = NULL;
    size_t capacity = 0;
    char *end = NULL;
    uintmax_t parsed;

    if (getline(&line, &capacity, stdin) < 0) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (line == end || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_even_parity((uint64_t)parsed) ? "Even parity" : "Odd parity");

    free(line);
    return EXIT_SUCCESS;
}