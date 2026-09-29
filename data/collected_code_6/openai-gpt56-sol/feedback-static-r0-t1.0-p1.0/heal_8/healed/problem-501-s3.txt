#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uintmax_t magnitude(intmax_t value)
{
    if (value < 0) {
        return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
    }

    return (uintmax_t)value;
}

static uintmax_t greatest_common_divisor(intmax_t first, intmax_t second)
{
    uintmax_t a = magnitude(first);
    uintmax_t b = magnitude(second);

    while (b != UINTMAX_C(0)) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int read_intmax(const char **cursor, intmax_t *value)
{
    char *end;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    *value = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE) {
        return 0;
    }

    *cursor = end;
    return 1;
}

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    char *buffer;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        int ch;

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *replacement;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;

            if (new_capacity <= capacity ||
                new_capacity > SIZE_MAX / sizeof(*buffer)) {
                free(buffer);
                return 0;
            }

            replacement = realloc(buffer, new_capacity * sizeof(*buffer));

            if (replacement == NULL) {
                free(buffer);
                return 0;
            }

            buffer = replacement;
            capacity = new_capacity;
        }

        ch = fgetc(stdin);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }

            break;
        }

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    const char *cursor;
    intmax_t first;
    intmax_t second;
    uintmax_t result;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!read_intmax(&cursor, &first) ||
        !read_intmax(&cursor, &second)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor != '\0' && isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (first == INTMAX_C(0) && second == INTMAX_C(0)) {
        fputs("The greatest common divisor of zero and zero is undefined\n",
              stderr);
        return EXIT_FAILURE;
    }

    result = greatest_common_divisor(first, second);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}