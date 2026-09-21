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

static int is_space_character(unsigned char character)
{
    return character == ' ' || character == '\t' ||
           character == '\n' || character == '\r' ||
           character == '\f' || character == '\v';
}

static int parse_intmax(const char **input, intmax_t *value)
{
    const char *cursor;
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    cursor = *input;

    while (is_space_character((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    parsed = strtoimax(cursor, &end, 10);

    if (end == cursor || errno == ERANGE) {
        return 0;
    }

    *input = end;
    *value = parsed;
    return 1;
}

static int read_line(FILE *stream, char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;

    if (stream == NULL || line == NULL) {
        return -1;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return -1;
    }

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                free(buffer);
                return -1;
            }

            if (length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        if (character == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return -1;
        }

        if (length + 1 >= capacity) {
            size_t required = length + 2;
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = required;
            } else {
                new_capacity = capacity * 2;

                if (new_capacity < required) {
                    new_capacity = required;
                }
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return -1;
            }

            new_buffer = realloc(buffer, new_capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)(unsigned char)character;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *line = NULL;
    const char *cursor;
    intmax_t first;
    intmax_t second;
    int read_status;
    int exit_status = EXIT_FAILURE;

    read_status = read_line(stdin, &line);

    if (read_status == 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (read_status < 0) {
        fputs("Failed to read input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = line;

    if (!parse_intmax(&cursor, &first) ||
        !parse_intmax(&cursor, &second)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (is_space_character((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n",
               greatest_common_divisor(first, second)) < 0) {
        fputs("Failed to write output\n", stderr);
        goto cleanup;
    }

    exit_status = EXIT_SUCCESS;

cleanup:
    free(line);
    return exit_status;
}