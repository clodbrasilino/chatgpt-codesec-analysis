#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t integer_sqrt(uint64_t value)
{
    uint64_t result = 0;
    uint64_t bit = UINT64_C(1) << 62;

    while (bit > value) {
        bit >>= 2;
    }

    while (bit != 0) {
        if (value >= result + bit) {
            value -= result + bit;
            result = (result >> 1) + bit;
        } else {
            result >>= 1;
        }

        bit >>= 2;
    }

    return result;
}

static uint64_t count_odd_factors_in_range(uint64_t lower, uint64_t upper)
{
    uint64_t count = upper - lower + UINT64_C(1);
    uint64_t squares = integer_sqrt(upper);

    if (lower != 0) {
        squares -= integer_sqrt(lower - UINT64_C(1));
    }

    return count - squares;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    start = *input;

    if (*start == '\0' || *start == '-' || *start == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (uint64_t)parsed;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;
    int ch = EOF;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        ch = fgetc(stream);

        if (ch == EOF || ch == '\n') {
            break;
        }

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

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (ferror(stream) || (ch == EOF && length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *buffer = NULL;
    const char *input;
    uint64_t lower;
    uint64_t upper;
    uint64_t result;

    if (!read_line(stdin, &buffer)) {
        return EXIT_FAILURE;
    }

    input = buffer;

    if (!parse_uint64(&input, &lower) ||
        !parse_uint64(&input, &upper)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*input)) {
        ++input;
    }

    if (*input != '\0' || lower > upper) {
        free(buffer);
        return EXIT_FAILURE;
    }

    result = count_odd_factors_in_range(lower, upper);

    if (printf("%" PRIu64 "\n", result) < 0) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);
    return EXIT_SUCCESS;
}