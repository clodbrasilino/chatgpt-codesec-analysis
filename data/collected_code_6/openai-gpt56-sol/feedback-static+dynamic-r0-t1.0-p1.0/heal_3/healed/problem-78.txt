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
    char *end = NULL;
    uintmax_t value;

    if (text == NULL || result == NULL || text[0] == '\0' || text[0] == '-') {
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
    char *end = NULL;
    uintmax_t value;

    if (text == NULL || result == NULL || text[0] == '\0' || text[0] == '-') {
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

static int read_token(char *buffer, size_t capacity)
{
    int ch;
    size_t length = 0;

    if (buffer == NULL || capacity < 2) {
        return 0;
    }

    do {
        ch = getchar();
    } while (ch != EOF && (ch == ' ' || ch == '\t' || ch == '\n' ||
                           ch == '\r' || ch == '\f' || ch == '\v'));

    if (ch == EOF) {
        return 0;
    }

    while (ch != EOF && ch != ' ' && ch != '\t' && ch != '\n' &&
           ch != '\r' && ch != '\f' && ch != '\v') {
        if (length + 1 >= capacity) {
            do {
                ch = getchar();
            } while (ch != EOF && ch != ' ' && ch != '\t' && ch != '\n' &&
                     ch != '\r' && ch != '\f' && ch != '\v');
            buffer[0] = '\0';
            return 0;
        }

        buffer[length++] = (char)ch;
        ch = getchar();
    }

    buffer[length] = '\0';
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
    uint64_t *values = NULL;

    if (!read_token(token, sizeof(token)) || !parse_size(token, &count)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count != 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(token, sizeof(token)) ||
            !parse_uint64(token, &values[i])) {
            fputs("Invalid input\n", stderr);
            free(values);
            return EXIT_FAILURE;
        }
    }

    printf("%zu\n", count_odd_set_bits(values, count));

    free(values);
    return EXIT_SUCCESS;
}