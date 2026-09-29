#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
 /* Possible weaknesses found:
  *  'INT_MAX' is defined in header '<limits.h>'; this is probably fixable by adding '#include <limits.h>'
  */

static int find_nth_non_multiple(uint64_t n, uint64_t divisor,
                                 uint64_t *result)
{
    uint64_t quotient;
    uint64_t remainder;

    if (n == 0 || divisor <= 1 || result == NULL) {
        return 0;
    }

    quotient = (n - 1) / (divisor - 1);
    remainder = (n - 1) % (divisor - 1);

    if (quotient > (UINT64_MAX - remainder - 1) / divisor) {
        return 0;
    }

    *result = quotient * divisor + remainder + 1;
    return 1;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    while (**cursor == ' ' || **cursor == '\t') {
        ++*cursor;
    }

    if (**cursor == '\0' || **cursor == '\n' || **cursor == '\r' ||
        **cursor == '+' || **cursor == '-') {
        return 0;
    }

    start = *cursor;
    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return 0;
    }

    *cursor = end;
    *value = (uint64_t)parsed;
    return 1;
}

static char *read_line(FILE *stream)
{
    char *buffer;
    size_t capacity = 128;
    size_t length = 0;

    if (stream == NULL) {
        return NULL;
    }

    buffer = malloc(capacity);
    if (buffer == NULL) {
        return NULL;
    }

    for (;;) {
        size_t available;

        if (length == SIZE_MAX - 1) {
            free(buffer);
            return NULL;
        }

        available = capacity - length;

        if (available < 2) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return NULL;
            }

            new_capacity = capacity * 2;
            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return NULL;
            }

            buffer = resized;
            capacity = new_capacity;
            available = capacity - length;
        }

        /* Possible weaknesses found:
         *  'INT_MAX' undeclared (first use in this function)
         *  each undeclared identifier is reported only once for each function it appears in
         *  use of undeclared identifier 'INT_MAX'
         */
        if (fgets(buffer + length, (int)(available > INT_MAX
                                            /* Possible weaknesses found:
                                             *  use of undeclared identifier 'INT_MAX'
                                             */
                                            ? INT_MAX
                                            : available),
                  stream) == NULL) {
            if (ferror(stream) || length == 0) {
                free(buffer);
                return NULL;
            }
            break;
        }

        while (buffer[length] != '\0' && buffer[length] != '\n') {
            ++length;
        }

        if (buffer[length] == '\n') {
            buffer[length] = '\0';
            return buffer;
        }

        if (feof(stream)) {
            break;
        }
    }

    buffer[length] = '\0';
    return buffer;
}

int main(void)
{
    char *input;
    const char *cursor;
    uint64_t n;
    uint64_t divisor;
    uint64_t result;

    input = read_line(stdin);
    if (input == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &n) ||
        !parse_uint64(&cursor, &divisor)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\r' || *cursor == '\n') {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!find_nth_non_multiple(n, divisor, &result)) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}