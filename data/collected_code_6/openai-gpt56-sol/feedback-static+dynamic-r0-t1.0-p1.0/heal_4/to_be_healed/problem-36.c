#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                         uint64_t n, unsigned int *digit)
{
    uint64_t remainder;

    if (denominator == 0 || n == 0 || digit == NULL) {
        return 0;
    }

    remainder = numerator % denominator;

    for (uint64_t i = 1; i < n; ++i) {
        remainder = (uint64_t)(((__uint128_t)remainder * 10U) % denominator);
    }

    *digit = (unsigned int)(((__uint128_t)remainder * 10U) / denominator);
    return 1;
}

static int parse_uint64(const char **input, uint64_t *value)
{
    const unsigned char *cursor;
    char *end;
    uintmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    cursor = (const unsigned char *)*input;

    while (isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor == '\0' || *cursor == '+' || *cursor == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax((const char *)cursor, &end, 10);

    if (errno == ERANGE || end == (const char *)cursor ||
        parsed > UINT64_MAX) {
        return 0;
    }

    *value = (uint64_t)parsed;
    *input = end;
    return 1;
}

static int read_line(char **line)
{
    char *buffer;
    size_t length = 0;
    size_t capacity = 128;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

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

        if (length >= capacity - 1) {
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

int main(void)
{
    char *buffer = NULL;
    const char *input;
    const unsigned char *cursor;
    uint64_t numerator;
    uint64_t denominator;
    uint64_t n;
    unsigned int digit;

    if (!read_line(&buffer)) {
        return EXIT_FAILURE;
    }

    input = buffer;

    if (!parse_uint64(&input, &numerator) ||
        !parse_uint64(&input, &denominator) ||
        !parse_uint64(&input, &n)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    cursor = (const unsigned char *)input;

    while (isspace(*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' ||
        !nth_fractional_digit(numerator, denominator, n, &digit)) {
        free(buffer);
        return EXIT_FAILURE;
    }

    free(buffer);

    if (printf("%u\n", digit) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}