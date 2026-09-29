#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_space(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

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

    if (text == NULL || result == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value > (uintmax_t)SIZE_MAX) {
        return 0;
    }

    *result = (size_t)value;
    return 1;
}

static int parse_uint64(const char *text, uint64_t *result)
{
    char *end = NULL;
    uintmax_t value;

    if (text == NULL || result == NULL || text[0] == '\0' ||
        text[0] == '-' || text[0] == '+') {
        return 0;
    }

    errno = 0;
    value = strtoumax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        value > (uintmax_t)UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

static int read_token(FILE *stream, char **result)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 32;
    int ch;

    if (stream == NULL || result == NULL) {
        return 0;
    }

    *result = NULL;

    do {
        ch = fgetc(stream);
        if (ch == EOF) {
            return 0;
        }
    } while (is_space(ch));

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        if (length >= capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;

        ch = fgetc(stream);
        if (ch == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (is_space(ch)) {
            break;
        }
    }

    buffer[length] = '\0';
    *result = buffer;
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
    char *token = NULL;
    uint64_t *values = NULL;
    size_t count;

    if (!read_token(stdin, &token) || !parse_size(token, &count)) {
        free(token);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(token);
    token = NULL;

    if (count > SIZE_MAX / sizeof(*values)) {
        fputs("Input size is too large\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > 0) {
        values = malloc(count * sizeof(*values));
        if (values == NULL) {
            fputs("Memory allocation failed\n", stderr);
            return EXIT_FAILURE;
        }
    }

    for (size_t i = 0; i < count; ++i) {
        if (!read_token(stdin, &token) ||
            !parse_uint64(token, &values[i])) {
            free(token);
            free(values);
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }

        free(token);
        token = NULL;
    }

    if (printf("%zu\n", count_odd_set_bits(values, count)) < 0) {
        free(values);
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    free(values);
    return EXIT_SUCCESS;
}