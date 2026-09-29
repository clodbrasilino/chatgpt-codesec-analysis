#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value >= 0) {
        return (uintmax_t)value;
    }

    return (uintmax_t)(-(value + 1)) + UINTMAX_C(1);
}

static uintmax_t greatest_common_divisor(intmax_t first, intmax_t second)
{
    uintmax_t a = magnitude(first);
    uintmax_t b = magnitude(second);

    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;

    if (stream == NULL || line == NULL) {
        return 0;
    }

    *line = NULL;
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
            if (ferror(stream) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
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

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int parse_input(const char *input, intmax_t *first, intmax_t *second)
{
    const char *cursor;
    char *end;
    intmax_t parsed_first;
    intmax_t parsed_second;

    if (input == NULL || first == NULL || second == NULL) {
        return 0;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed_first = strtoimax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        return 0;
    }

    cursor = end;

    if (*cursor == '\0' || !isspace((unsigned char)*cursor)) {
        return 0;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed_second = strtoimax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *first = parsed_first;
    *second = parsed_second;
    return 1;
}

int main(void)
{
    char *input = NULL;
    intmax_t first;
    intmax_t second;
    uintmax_t result;

    if (!read_line(stdin, &input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!parse_input(input, &first, &second)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);
    result = greatest_common_divisor(first, second);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}