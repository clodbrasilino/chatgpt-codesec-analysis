#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t greatest_common_divisor(uint64_t a, uint64_t b)
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
        uint64_t numerator = (uint64_t)n - k + i;
        uint64_t denominator = i;
        uint64_t divisor;

        divisor = greatest_common_divisor(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;

        divisor = greatest_common_divisor(value, denominator);
        value /= divisor;
        denominator /= divisor;

        if (denominator != 1 ||
            (numerator != 0 && value > UINT64_MAX / numerator)) {
            return 0;
        }

        value *= numerator;
    }

    *result = value;
    return 1;
}

static int discard_remaining_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static int read_line(char **line)
{
    enum { MAX_INPUT_LENGTH = 4096 };
    char *buffer;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;

    buffer = malloc((size_t)MAX_INPUT_LENGTH + 1U);
    if (buffer == NULL) {
        return 0;
    }

    while (length < MAX_INPUT_LENGTH) {
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

        buffer[length++] = (char)(unsigned char)ch;
    }

    if (length == MAX_INPUT_LENGTH) {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            if (!discard_remaining_line()) {
                free(buffer);
                return 0;
            }

            free(buffer);
            return 0;
        }

        if (ch == EOF && ferror(stdin)) {
            free(buffer);
            return 0;
        }
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int parse_uint32(char **cursor, uint32_t *value)
{
    char *start;
    char *end;
    uintmax_t parsed;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return 0;
    }

    start = *cursor;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0' || *start == '-' || *start == '+') {
        return 0;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT32_MAX) {
        return 0;
    }

    *value = (uint32_t)parsed;
    *cursor = end;
    return 1;
}

int main(void)
{
    char *input = NULL;
    char *cursor;
    uint32_t n;
    uint32_t k;
    uint64_t result;

    if (fputs("Enter n and k: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    if (!read_line(&input)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint32(&cursor, &n) ||
        !parse_uint32(&cursor, &k)) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0') {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (!binomial_coefficient(n, k, &result)) {
        fputs("Invalid arguments or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}