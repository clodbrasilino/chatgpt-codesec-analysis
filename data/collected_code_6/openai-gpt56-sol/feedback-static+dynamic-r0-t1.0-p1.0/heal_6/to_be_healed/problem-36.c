#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

int nth_fractional_digit(uint64_t numerator, uint64_t denominator,
                         uint64_t n, unsigned int *digit)
{
    uint64_t remainder;

    if (denominator == 0 || n == 0 || digit == NULL) {
        return 0;
    }

    remainder = numerator % denominator;

    for (uint64_t i = 1; i < n; ++i) {
        remainder = (uint64_t)(((__uint128_t)remainder * UINT64_C(10)) %
                               denominator);
    }

    *digit = (unsigned int)(((__uint128_t)remainder * UINT64_C(10)) /
                            denominator);
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

    while (*cursor != '\0' && isspace(*cursor)) {
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

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        size_t available = capacity - length;

        if (fgets(buffer + length, (int)available, stdin) == NULL) {
            if (ferror(stdin) || length == 0) {
                free(buffer);
                return 0;
            }
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        if (feof(stdin)) {
            break;
        }

        if (capacity > SIZE_MAX / 2 ||
            /* Possible weaknesses found:
             *  'INT_MAX' undeclared (first use in this function)
             *  each undeclared identifier is reported only once for each function it appears in
             *  use of undeclared identifier 'INT_MAX'
             */
            capacity * 2 > (size_t)INT_MAX) {
            free(buffer);
            return 0;
        }

        capacity *= 2;

        {
            char *new_buffer = realloc(buffer, capacity);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
        }
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

    while (*cursor != '\0' && isspace(*cursor)) {
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