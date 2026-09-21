#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int has_odd_set_bits(uint64_t value)
{
    int parity = 0;

    while (value != UINT64_C(0)) {
        parity ^= 1;
        value &= value - UINT64_C(1);
    }

    return parity;
}

static int read_uint64(uint64_t *value)
{
    char *line = NULL;
    size_t capacity = 0U;
    char *end = NULL;
    uintmax_t parsed;
    ssize_t length;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    if (length == 0 || line[length - 1] != '\n') {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtoumax(line, &end, 10);

    if (end == line || errno == ERANGE || parsed > UINT64_MAX) {
        free(line);
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = (uint64_t)parsed;
    free(line);
    return 1;
}

static size_t count_odd_set_bits(const uint64_t *values, size_t count)
{
    size_t result = 0U;

    for (size_t i = 0U; i < count; ++i) {
        if (has_odd_set_bits(values[i])) {
            ++result;
        }
    }

    return result;
}

int main(void)
{
    uint64_t input_count;
    uint64_t *values = NULL;
    size_t count;

    if (!read_uint64(&input_count) || input_count > SIZE_MAX) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)input_count;

    if (count > SIZE_MAX / sizeof *values) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0U) {
        values = malloc(count * sizeof *values);
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0U; i < count; ++i) {
        if (!read_uint64(&values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_odd_set_bits(values, count));

    free(values);
    return EXIT_SUCCESS;
}