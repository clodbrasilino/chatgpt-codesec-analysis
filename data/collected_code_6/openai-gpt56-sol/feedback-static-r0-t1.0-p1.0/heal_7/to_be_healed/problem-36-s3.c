#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                                uint64_t n, unsigned int *digit)
{
    uint64_t remainder;

    if (denominator == 0 || n == 0 || digit == NULL) {
        return -1;
    }

    remainder = numerator % denominator;

    for (uint64_t position = 0; position < n; ++position) {
        unsigned int quotient_digit = 0;

        for (unsigned int i = 0; i < 10; ++i) {
            if (remainder >= denominator - remainder) {
                remainder -= denominator - remainder;
                ++quotient_digit;
            } else {
                remainder += remainder;
            }
        }

        *digit = quotient_digit;
    }

    return 0;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return -1;
    }

    while (**cursor == ' ' || **cursor == '\t' ||
           **cursor == '\r' || **cursor == '\n' ||
           **cursor == '\f' || **cursor == '\v') {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '+' || **cursor == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || parsed > UINT64_MAX) {
        return -1;
    }

    *value = (uint64_t)parsed;
    *cursor = end;
    return 0;
}

static int read_line(char **line)
{
    size_t capacity = 128;
    size_t length = 0;
    char *buffer;
    int ch;

    if (line == NULL) {
        return -1;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF && ch != '\n') {
        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return -1;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return -1;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(buffer);
        return -1;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 0;
}

int main(void)
{
    char *input;
    const char *cursor;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t n;
    unsigned int digit;

    if (read_line(&input) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (parse_uint64(&cursor, &numerator) != 0 ||
        parse_uint64(&cursor, &denominator) != 0 ||
        parse_uint64(&cursor, &n) != 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\r' || *cursor == '\n' ||
           *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (nth_fractional_digit(numerator, denominator, n, &digit) != 0) {
        fputs("Unable to calculate digit\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}