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

static int read_line(char **line)
{
    size_t length = 0;
    size_t capacity = 128;
    int ch;
    char *buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
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

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

int main(void)
{
    char *input;
    char *cursor;
    char *end;
    intmax_t first;
    intmax_t second;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;
    errno = 0;
    first = strtoimax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    second = strtoimax(cursor, &end, 10);

    if (cursor == end || errno == ERANGE) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIuMAX "\n", greatest_common_divisor(first, second));
    free(input);
    return EXIT_SUCCESS;
}