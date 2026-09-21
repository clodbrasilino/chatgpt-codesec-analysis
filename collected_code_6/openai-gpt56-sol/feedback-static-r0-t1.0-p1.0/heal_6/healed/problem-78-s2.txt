#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int read_uintmax(uintmax_t *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length = getline(&line, &capacity, stdin);

    if (value == NULL || length < 0) {
        free(line);
        return 0;
    }

    if (length == 0 || line[length - 1] != '\n') {
        free(line);
        return 0;
    }

    line[--length] = '\0';

    if (length > 0 && line[length - 1] == '\r') {
        line[--length] = '\0';
    }

    char *cursor = line;

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        free(line);
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t result = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = result;
    free(line);
    return 1;
}

static unsigned int has_odd_parity(uint64_t value)
{
    unsigned int parity = 0;

    while (value != UINT64_C(0)) {
        parity ^= 1U;
        value &= value - UINT64_C(1);
    }

    return parity;
}

int main(void)
{
    uintmax_t input_count;

    if (!read_uintmax(&input_count) || input_count > (uintmax_t)SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    size_t count = (size_t)input_count;
    size_t odd_count = 0;

    for (size_t i = 0; i < count; ++i) {
        uintmax_t input_value;

        if (!read_uintmax(&input_value) ||
            input_value > (uintmax_t)UINT64_MAX) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        odd_count += (size_t)has_odd_parity((uint64_t)input_value);
    }

    if (printf("%zu\n", odd_count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}