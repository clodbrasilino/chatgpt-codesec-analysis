#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 4096 };

static uintmax_t gcd(uintmax_t a, uintmax_t b)
{
    while (b != 0) {
        uintmax_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static uintmax_t magnitude(intmax_t value)
{
    if (value < 0) {
        return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
    }

    return (uintmax_t)value;
}

static int is_space_char(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int consume_line_remainder(void)
{
    char buffer[256];

    while (fgets(buffer, sizeof buffer, stdin) != NULL) {
        size_t i = 0;

        while (buffer[i] != '\0') {
            if (buffer[i] == '\n') {
                return 1;
            }
            ++i;
        }
    }

    return ferror(stdin) ? 0 : 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t capacity = (size_t)MAX_INPUT_LENGTH + 2U;
    size_t length = 0;

    if (line == NULL || capacity > (size_t)INT_MAX) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        free(buffer);
        return 0;
    }

    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
    } else if (length > (size_t)MAX_INPUT_LENGTH) {
        free(buffer);
        if (!consume_line_remainder()) {
            return 0;
        }
        return 0;
    } else if (length == (size_t)MAX_INPUT_LENGTH) {
        char probe[2];

        if (fgets(probe, sizeof probe, stdin) == NULL) {
            if (ferror(stdin)) {
                free(buffer);
                return 0;
            }
        } else if (probe[0] != '\n') {
            free(buffer);
            if (!consume_line_remainder()) {
                return 0;
            }
            return 0;
        }
    }

    *line = buffer;
    return 1;
}

static int parse_integer(char **cursor, intmax_t *value)
{
    char *end;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (is_space_char(**cursor)) {
        ++*cursor;
    }

    errno = 0;
    *value = strtoimax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE) {
        return 0;
    }

    *cursor = end;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *cursor;
    intmax_t first;
    intmax_t second;
    uintmax_t result;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_integer(&cursor, &first) ||
        !parse_integer(&cursor, &second)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_char(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    result = gcd(magnitude(first), magnitude(second));
    free(input);

    if (printf("%" PRIuMAX "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}