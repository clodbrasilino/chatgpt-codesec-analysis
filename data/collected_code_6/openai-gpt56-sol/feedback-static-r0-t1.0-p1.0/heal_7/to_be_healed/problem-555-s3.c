#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t sum;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    sum = (__uint128_t)n * ((__uint128_t)n + 1U) / 2U;
    difference = sum * sum - sum;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

static int read_value(uint64_t *result)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *start;
    char *end;
    uintmax_t value;
    size_t length;

    if (result == NULL || fgets(buffer, sizeof buffer, stdin) == NULL) {
        return 0;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(buffer);

    if (length == 0U || buffer[length - 1U] != '\n') {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        int ch = getchar();

        while (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        }

        return 0;
    }

    buffer[length - 1U] = '\0';
    start = buffer;

    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '-' || *start == '\0') {
        return 0;
    }

    errno = 0;
    value = strtoumax(start, &end, 10);

    if (start == end || errno == ERANGE || value > UINT64_MAX) {
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *result = (uint64_t)value;
    return 1;
}

int main(void)
{
    uint64_t value;
    uint64_t difference;

    if (!read_value(&value)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!calculate_difference(value, &difference)) {
        fputs("Result is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", difference);
    return EXIT_SUCCESS;
}