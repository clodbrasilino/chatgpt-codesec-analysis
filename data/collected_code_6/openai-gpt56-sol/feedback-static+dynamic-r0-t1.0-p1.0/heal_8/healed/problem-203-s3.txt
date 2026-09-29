#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned int hamming_distance(uint32_t first, uint32_t second)
{
    uint32_t difference = first ^ second;
    unsigned int distance = 0U;

    while (difference != UINT32_C(0)) {
        difference &= difference - UINT32_C(1);
        ++distance;
    }

    return distance;
}

static int parse_uint32(const char **input, uint32_t *value)
{
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0' || **input == '-' || **input == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT32_MAX) {
        return 0;
    }

    *value = (uint32_t)parsed;
    *input = end;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t length;
    size_t capacity;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    capacity = 128U;
    length = 0U;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0U) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length >= capacity - 1U) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2U) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2U;
            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    const char *cursor;
    uint32_t first;
    uint32_t second;

    if (!read_line(stdin, &input)) {
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint32(&cursor, &first) ||
        !parse_uint32(&cursor, &second)) {
        free(input);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%u\n", hamming_distance(first, second)) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}