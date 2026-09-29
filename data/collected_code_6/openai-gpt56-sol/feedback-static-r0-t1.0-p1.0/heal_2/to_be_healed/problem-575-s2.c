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

static int parse_input(uint64_t *n, uint64_t *divisor)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[256];
    char *cursor;
    char *end;
    uintmax_t value;

    if (n == NULL || divisor == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    cursor = buffer;

    errno = 0;
    value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || value > UINT64_MAX) {
        return 0;
    }
    *n = (uint64_t)value;
    cursor = end;

    errno = 0;
    value = strtoumax(cursor, &end, 10);
    if (cursor == end || errno == ERANGE || value > UINT64_MAX) {
        return 0;
    }
    *divisor = (uint64_t)value;
    cursor = end;

    while (*cursor == ' ' || *cursor == '\t' ||
           *cursor == '\n' || *cursor == '\r' ||
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

    if (!parse_input(&n, &divisor)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
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