#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int discard_line(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

static int read_uintmax(uintmax_t *value)
{
    char buffer[256];

    if (value == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    size_t length = 0U;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        discard_line();
        return 0;
    }

    if (length == 0U || buffer[length - 1U] != '\n') {
        if (!feof(stdin)) {
            discard_line();
        }
        return 0;
    }

    buffer[--length] = '\0';

    if (length > 0U && buffer[length - 1U] == '\r') {
        buffer[--length] = '\0';
    }

    char *cursor = buffer;
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\f' ||
           *cursor == '\v') {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '-') {
        return 0;
    }

    errno = 0;
    char *end = NULL;
    uintmax_t result = strtoumax(cursor, &end, 10);

    if (errno == ERANGE || end == cursor) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\f' ||
           *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = result;
    return 1;
}

static unsigned int has_odd_parity(uint64_t value)
{
    unsigned int parity = 0U;

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
    size_t odd_count = 0U;

    for (size_t i = 0U; i < count; ++i) {
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