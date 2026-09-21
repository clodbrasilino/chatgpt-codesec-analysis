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

    while (**cursor == ' ' || **cursor == '\t' ||
           **cursor == '\r' || **cursor == '\n' ||
           **cursor == '\f' || **cursor == '\v') {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '+' || **cursor == '-') {
        return -1;
    }

    errno = 0;
    *value = strtoumax(*cursor, &end, 10);

    if (end == *cursor || errno == ERANGE || *value > UINT64_MAX) {
        return -1;
    }

    *cursor = end;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    size_t length = 0;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t n;
    unsigned int digit;
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (length == capacity) {
            size_t new_capacity = capacity == 0 ? 128 : capacity * 2;
            char *new_input;

            if (new_capacity <= capacity) {
                free(input);
                fputs("Invalid input\n", stderr);
                return 1;
            }

            new_input = realloc(input, new_capacity);
            if (new_input == NULL) {
                free(input);
                fputs("Invalid input\n", stderr);
                return 1;
            }

            input = new_input;
            capacity = new_capacity;
        }

        input[length++] = (char)ch;
    }

    if (ch == EOF && length == 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (length == capacity) {
        char *new_input = realloc(input, capacity + 1);

        if (new_input == NULL) {
            free(input);
            fputs("Invalid input\n", stderr);
            return 1;
        }

        input = new_input;
    }

    input[length] = '\0';

    {
        const char *cursor = input;

        if (parse_uint64(&cursor, &numerator) != 0 ||
            parse_uint64(&cursor, &denominator) != 0 ||
            parse_uint64(&cursor, &n) != 0) {
            free(input);
            fputs("Invalid input\n", stderr);
            return 1;
        }

        while (*cursor == ' ' || *cursor == '\t' ||
               *cursor == '\r' || *cursor == '\n' ||
               *cursor == '\f' || *cursor == '\v') {
            ++cursor;
        }

        if (*cursor != '\0') {
            free(input);
            fputs("Invalid input\n", stderr);
            return 1;
        }
    }

    free(input);

    if (nth_fractional_digit(numerator, denominator, n, &digit) != 0) {
        fputs("Unable to calculate digit\n", stderr);
        return 1;
    }

    printf("%u\n", digit);
    return 0;
}