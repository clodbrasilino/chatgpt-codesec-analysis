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

    return (uintmax_t)(-(value + INTMAX_C(1))) + UINTMAX_C(1);
}

static uintmax_t digit_distance(intmax_t first, intmax_t second)
{
    uintmax_t left = magnitude(first);
    uintmax_t right = magnitude(second);
    uintmax_t distance = 0;

    do {
        uintmax_t left_digit = left % UINTMAX_C(10);
        uintmax_t right_digit = right % UINTMAX_C(10);

        if (left_digit >= right_digit) {
            distance += left_digit - right_digit;
        } else {
            distance += right_digit - left_digit;
        }

        left /= UINTMAX_C(10);
        right /= UINTMAX_C(10);
    } while (left != 0 || right != 0);

    return distance;
}

static int read_line(FILE *stream, char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 64;

    if (stream == NULL || line == NULL) {
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

        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stream);

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

        buffer[length++] = (char)(unsigned char)ch;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;
    int result = EXIT_FAILURE;

    if (!read_line(stdin, &input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    first = strtoimax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    cursor = end;
    if (*cursor == '\0' || !isspace((unsigned char)*cursor)) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    errno = 0;
    second = strtoimax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE) {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        goto cleanup;
    }

    if (printf("%" PRIuMAX "\n", digit_distance(first, second)) < 0) {
        goto cleanup;
    }

    result = EXIT_SUCCESS;

cleanup:
    free(input);
    return result;
}