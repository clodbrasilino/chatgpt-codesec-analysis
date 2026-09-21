#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t gcd_u64(uint64_t a, uint64_t b)
{
    while (b != 0) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int binomial_coefficient(uint32_t n, uint32_t k, uint64_t *result)
{
    uint64_t value = 1;

    if (result == NULL || k > n) {
        return 0;
    }

    if (k > n - k) {
        k = n - k;
    }

    for (uint32_t i = 1; i <= k; ++i) {
        uint64_t numerator = (uint64_t)(n - k) + i;
        uint64_t denominator = i;
        uint64_t divisor = gcd_u64(numerator, denominator);

        numerator /= divisor;
        denominator /= divisor;

        divisor = gcd_u64(value, denominator);
        value /= divisor;
        denominator /= divisor;

        if (denominator != 1 || value > UINT64_MAX / numerator) {
            return 0;
        }

        value *= numerator;
    }

    *result = value;
    return 1;
}

static int read_line(char **line)
{
    size_t size = 128;
    size_t length = 0;
    char *buffer = malloc(size);

    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            if (ch == EOF && ferror(stdin)) {
                free(buffer);
                return 0;
            }

            if (ch == EOF && length == 0) {
                free(buffer);
                return 0;
            }

            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        if (length + 1 >= size) {
            if (size > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            size_t new_size = size * 2;
            char *new_buffer = realloc(buffer, new_size);

            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            size = new_size;
        }

        buffer[length++] = (char)ch;
    }
}

static int parse_uint32(const char **cursor, uint32_t *value)
{
    const char *start = *cursor;
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '+' || *start == '-') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (errno == ERANGE || end == start || parsed > UINT32_MAX) {
        return 0;
    }

    *value = (uint32_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    char *line = NULL;
    const char *cursor;
    uint32_t n;
    uint32_t k;
    uint64_t result;

    if (!read_line(&line)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = line;

    if (!parse_uint32(&cursor, &n) || !parse_uint32(&cursor, &k)) {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(line);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(line);

    if (!binomial_coefficient(n, k, &result)) {
        fputs("Invalid arguments or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}