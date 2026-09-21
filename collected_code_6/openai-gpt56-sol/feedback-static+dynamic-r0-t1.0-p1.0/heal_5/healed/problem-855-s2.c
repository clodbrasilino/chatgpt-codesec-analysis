#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static bool has_even_parity(uint64_t value)
{
    bool even = true;

    while (value != UINT64_C(0)) {
        even = !even;
        value &= value - UINT64_C(1);
    }

    return even;
}

static bool read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *start;
    char *end;
    uintmax_t parsed;

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return false;
    }

    if (length > 0 && line[length - 1] == '\n') {
        line[length - 1] = '\0';
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-') {
        free(line);
        return false;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return false;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return false;
    }

    *value = (uint64_t)parsed;
    free(line);
    return true;
}

int main(void)
{
    uint64_t value;

    if (!read_uint64(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(has_even_parity(value) ? "Even parity" : "Odd parity");
    return EXIT_SUCCESS;
}