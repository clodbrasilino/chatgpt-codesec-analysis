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
        uint64_t next_remainder = 0;

        for (unsigned int bit = 0; bit < 4; ++bit) {
            next_remainder *= 2;

            if (((UINT64_C(10) >> (3U - bit)) & UINT64_C(1)) != 0) {
                if (remainder >= denominator - next_remainder) {
                    next_remainder -= denominator - remainder;
                    ++quotient_digit;
                } else {
                    next_remainder += remainder;
                }
            }

            if (bit != 3U) {
                quotient_digit *= 2;
            }
        }

        remainder = next_remainder;
        *digit = quotient_digit;
    }

    return 1;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (**input == ' ' || **input == '\t' ||
           **input == '\n' || **input == '\r' ||
           **input == '\f' || **input == '\v') {
        ++*input;
    }

    if (**input == '\0' || **input == '-' || **input == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(*input, &end, 10);

    if (end == *input || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *input = end;
    *value = (uint64_t)parsed;
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
        /* Possible weaknesses found:
         * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
         */
        char chunk[256];

        if (fgets(chunk, sizeof chunk, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        size_t chunk_length = 0;
        while (chunk_length < sizeof chunk &&
               chunk[chunk_length] != '\0' &&
               chunk[chunk_length] != '\n') {
            ++chunk_length;
        }

        if (chunk_length > SIZE_MAX - length - 1) {
            free(buffer);
            return 0;
        }

        size_t required = length + chunk_length + 1;
        if (required > capacity) {
            size_t new_capacity = capacity;

            while (new_capacity < required) {
                if (new_capacity > SIZE_MAX / 2) {
                    new_capacity = required;
                    break;
                }
                new_capacity *= 2;
            }

            char *resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return 0;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        for (size_t i = 0; i < chunk_length; ++i) {
            buffer[length + i] = chunk[i];
        }
        length += chunk_length;

        if (chunk_length < sizeof chunk - 1 &&
            chunk[chunk_length] == '\n') {
            break;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int is_space_character(char ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' ||
           ch == '\r' || ch == '\f' || ch == '\v';
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
        !parse_uint64(&cursor, &position)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (is_space_character(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
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