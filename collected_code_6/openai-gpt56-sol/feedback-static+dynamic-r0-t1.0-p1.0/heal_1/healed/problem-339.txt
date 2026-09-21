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
    if (divisor == NULL || occurrences == NULL || lower == 0U ||
        lower > upper) {
        return -1;
    }

    *divisor = 1U;
    *occurrences = divisor_occurrences(1U, lower, upper);

    for (uint64_t candidate = 2U; candidate <= upper / 2U; ++candidate) {
        uint64_t count = divisor_occurrences(candidate, lower, upper);

        if (count > *occurrences) {
            *divisor = candidate;
            *occurrences = count;
        }
    }

    return 0;
}

static int parse_interval(const char *input, uint64_t *lower, uint64_t *upper)
{
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (input == NULL || lower == NULL || upper == NULL) {
        return -1;
    }

    errno = 0;
    first = strtoumax(input, &end, 10);
    if (input == end || errno == ERANGE || first > UINT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end == '\0' || *end == '-') {
        return -1;
    }

    input = end;
    errno = 0;
    second = strtoumax(input, &end, 10);
    if (input == end || errno == ERANGE || second > UINT64_MAX) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *lower = (uint64_t)first;
    *upper = (uint64_t)second;
    return 0;
}

int main(void)
{
    char input[256];
    uint64_t lower;
    uint64_t upper;
    uint64_t divisor;
    uint64_t occurrences;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (parse_interval(input, &lower, &upper) != 0) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_max_occurring_divisor(lower, upper, &divisor, &occurrences) != 0) {
        fputs("Invalid interval\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Divisor: %" PRIu64 "\nOccurrences: %" PRIu64 "\n",
               divisor, occurrences) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}