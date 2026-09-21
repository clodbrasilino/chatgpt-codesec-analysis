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

static int parse_size(const char *text, size_t *result)
{
    char *end;
    uintmax_t value;

    if (text[0] == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value > SIZE_MAX) {
        return 0;
    }

    *result = (size_t)value;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *result)
{
    char *end;
    uintmax_t value;

    if (text[0] == '-') {
        return 0;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

static size_t count_odd_set_bits(const uint64_t *values, size_t count)
{
    size_t result = 0;

    for (size_t i = 0; i < count; ++i) {
        if (has_odd_set_bits(values[i])) {
            ++result;
        }
    }

    return result;
}

int main(void)
{
    char token[128];
    size_t count;

    if (scanf("%127s", token) != 1 || !parse_size(token, &count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(uint64_t)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    uint64_t *values = NULL;

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (scanf("%127s", token) != 1 || !parse_uint64(token, &values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_odd_set_bits(values, count));

    free(values);
    return EXIT_SUCCESS;
}