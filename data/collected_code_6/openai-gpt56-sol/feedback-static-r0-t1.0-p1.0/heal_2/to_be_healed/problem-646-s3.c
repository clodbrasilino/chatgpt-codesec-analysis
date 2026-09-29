#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int count_cubes(uint64_t n, uint64_t k, uint64_t *result)
{
    uint64_t per_side;
    uint64_t square;

    if (result == NULL || k == 0 || k > n) {
        return 0;
    }

    per_side = n / k;

    if (per_side != 0 && per_side > UINT64_MAX / per_side) {
        return 0;
    }

    square = per_side * per_side;

    if (per_side != 0 && square > UINT64_MAX / per_side) {
        return 0;
    }

    *result = square * per_side;
    return 1;
}

static int read_uint64_pair(uint64_t *n, uint64_t *k)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *cursor;
    char *end;
    uintmax_t first;
    uintmax_t second;

    if (n == NULL || k == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    cursor = buffer;

    errno = 0;
    first = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || first > UINT64_MAX) {
        return 0;
    }

    cursor = end;
    errno = 0;
    second = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || second > UINT64_MAX) {
        return 0;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *n = (uint64_t)first;
    *k = (uint64_t)second;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t k;
    uint64_t result;

    if (!read_uint64_pair(&n, &k)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_cubes(n, k, &result)) {
        fputs("Invalid dimensions or result overflow\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}