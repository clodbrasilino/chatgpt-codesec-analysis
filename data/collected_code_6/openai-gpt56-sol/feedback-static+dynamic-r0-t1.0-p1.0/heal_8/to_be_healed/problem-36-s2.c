#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                                uint64_t position, unsigned int *digit)
{
    uint64_t remainder;

    if (denominator == 0 || position == 0 || digit == NULL) {
        return 0;
    }

    remainder = numerator % denominator;

    for (uint64_t i = 0; i < position; ++i) {
        unsigned int quotient_digit = 0;

        for (unsigned int bit = 0; bit < 4; ++bit) {
            quotient_digit <<= 1;

            if (remainder >= denominator - remainder) {
                remainder -= denominator - remainder;
                ++quotient_digit;
            } else {
                remainder += remainder;
            }
        }

        if (quotient_digit >= 10) {
            quotient_digit -= 10;
            remainder -= denominator;
        }

        *digit = quotient_digit;
    }

    return 1;
}

static int is_space_character(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (is_space_character(**cursor)) {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '-' || **cursor == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (uint64_t)parsed;
    return 1;
}

static int only_whitespace_remains(const char *cursor)
{
    if (cursor == NULL) {
        return 0;
    }

    while (is_space_character(*cursor)) {
        ++cursor;
    }

    return *cursor == '\0';
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
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == EOF) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        if (ch == '\n') {
            break;
        }

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return 0;
        }

        if (length + 1 >= capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= capacity) {
                free(buffer);
                return 0;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
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
    char *input = NULL;
    const char *cursor;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t position;
    unsigned int digit;

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &numerator) ||
        !parse_uint64(&cursor, &denominator) ||
        !parse_uint64(&cursor, &position) ||
        !only_whitespace_remains(cursor)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!nth_fractional_digit(numerator, denominator, position, &digit)) {
        fputs("Unable to calculate digit\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}