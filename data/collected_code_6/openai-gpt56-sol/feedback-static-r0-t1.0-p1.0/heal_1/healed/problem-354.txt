#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int arithmetic_term(int64_t first, int64_t difference, int64_t term,
                           int64_t *result)
{
    int64_t steps;

    if (result == NULL || term < 1) {
        return 0;
    }

    steps = term - 1;

    if (difference > 0 && steps > (INT64_MAX - first) / difference) {
        return 0;
    }

    if (difference < 0) {
        uint64_t magnitude = (uint64_t)(-(difference + 1)) + 1U;
        uint64_t distance = (uint64_t)first - (uint64_t)INT64_MIN;

        if ((uint64_t)steps > distance / magnitude) {
            return 0;
        }
    }

    *result = first + steps * difference;
    return 1;
}

static int parse_int64(const char **input, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (input == NULL || *input == NULL || value == NULL) {
        return 0;
    }

    while (**input == ' ' || **input == '\t' || **input == '\n' ||
           **input == '\r' || **input == '\f' || **input == '\v') {
        ++*input;
    }

    if (**input == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(*input, &end, 10);

    if (end == *input || errno == ERANGE ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    *input = end;
    return 1;
}

int main(void)
{
    char buffer[256];
    const char *input;
    int64_t first;
    int64_t difference;
    int64_t term;
    int64_t result;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    input = buffer;

    if (!parse_int64(&input, &first) ||
        !parse_int64(&input, &difference) ||
        !parse_int64(&input, &term)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    while (*input == ' ' || *input == '\t' || *input == '\n' ||
           *input == '\r' || *input == '\f' || *input == '\v') {
        ++input;
    }

    if (*input != '\0') {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!arithmetic_term(first, difference, term, &result)) {
        fputs("Invalid term or arithmetic overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRId64 "\n", result);
    return EXIT_SUCCESS;
}