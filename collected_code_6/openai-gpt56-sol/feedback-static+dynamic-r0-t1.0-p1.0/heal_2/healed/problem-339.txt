#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <ctype.h>
#include <errno.h>

static uint64_t divisor_occurrences(uint64_t divisor, uint64_t lower,
                                    uint64_t upper)
{
    return upper / divisor - (lower - 1U) / divisor;
}

static int find_max_occurring_divisor(uint64_t lower, uint64_t upper,
                                      uint64_t *divisor,
                                      uint64_t *occurrences)
{
    if (divisor == NULL || occurrences == NULL ||
        lower == 0U || lower > upper) {
        return -1;
    }

    *divisor = 1U;
    *occurrences = upper - lower + 1U;

    return 0;
}

static int parse_uint64(const char **cursor, uint64_t *value)
{
    const char *start;
    char *end;
    uintmax_t parsed;

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    start = *cursor;

    if (*start == '\0' || *start == '+' || *start == '-') {
        return -1;
    }

    errno = 0;
    parsed = strtoumax(start, &end, 10);

    if (end == start || errno == ERANGE || parsed > UINT64_MAX) {
        return -1;
    }

    *cursor = end;
    *value = (uint64_t)parsed;
    return 0;
}

static int parse_interval(const char *input, uint64_t *lower, uint64_t *upper)
{
    const char *cursor;

    if (input == NULL || lower == NULL || upper == NULL) {
        return -1;
    }

    cursor = input;

    if (parse_uint64(&cursor, lower) != 0 ||
        parse_uint64(&cursor, upper) != 0) {
        return -1;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    return *cursor == '\0' ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0U;
    ssize_t length;
    uint64_t lower;
    uint64_t upper;
    uint64_t divisor;
    uint64_t occurrences;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_interval(input, &lower, &upper) != 0) {
        free(input);
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (find_max_occurring_divisor(lower, upper,
                                   &divisor, &occurrences) != 0) {
        fputs("Invalid interval\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Divisor: %" PRIu64 "\nOccurrences: %" PRIu64 "\n",
               divisor, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}