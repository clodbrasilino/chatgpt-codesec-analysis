#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_nth_non_multiple(uint64_t n, uint64_t divisor, uint64_t *result)
{
    uint64_t block;
    uint64_t offset;

    if (n == 0 || divisor <= 1 || result == NULL) {
        return 0;
    }

    block = (n - 1) / (divisor - 1);
    offset = (n - 1) % (divisor - 1) + 1;

    if (block > (UINT64_MAX - offset) / divisor) {
        return 0;
    }

    *result = block * divisor + offset;
    return 1;
}

static int read_uint64_pair(uint64_t *first, uint64_t *second)
{
    char line[256];
    char *cursor;
    char *end;
    uintmax_t value;

    if (first == NULL || second == NULL ||
        fgets(line, sizeof line, stdin) == NULL) {
        return 0;
    }

    cursor = line;

    errno = 0;
    value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || value > UINT64_MAX) {
        return 0;
    }
    *first = (uint64_t)value;
    cursor = end;

    errno = 0;
    value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || value > UINT64_MAX) {
        return 0;
    }
    *second = (uint64_t)value;
    cursor = end;

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\r' || *cursor == '\n' ||
           *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    return *cursor == '\0';
}

int main(void)
{
    uint64_t n;
    uint64_t divisor;
    uint64_t result;

    if (!read_uint64_pair(&n, &divisor)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_nth_non_multiple(n, divisor, &result)) {
        fputs("Unable to compute result\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}