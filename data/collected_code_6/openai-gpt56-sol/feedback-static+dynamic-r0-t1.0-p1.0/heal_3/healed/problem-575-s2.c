#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_nth_non_multiple(uint64_t n, uint64_t divisor, uint64_t *result)
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

int main(void)
{
    enum { INPUT_SIZE = 256 };
    char input[INPUT_SIZE];
    const char *cursor;
    uint64_t n;
    uint64_t divisor;
    uint64_t result;
    int character;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    cursor = input;

    if (!parse_uint64(&cursor, &n) ||
        !parse_uint64(&cursor, &divisor)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\n' || *cursor == '\r') {
        ++cursor;
    }

    if (*cursor != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL) {
        character = fgetc(stdin);
        if (character != '\n' && character != EOF) {
            while ((character = fgetc(stdin)) != '\n' && character != EOF) {
            }
            fputs("Input too large\n", stderr);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (!find_nth_non_multiple(n, divisor, &result)) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%" PRIu64 "\n", result) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}