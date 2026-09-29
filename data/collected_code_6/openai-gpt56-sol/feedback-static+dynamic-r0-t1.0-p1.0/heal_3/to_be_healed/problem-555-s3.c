#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int calculate_difference(uint64_t n, uint64_t *result)
{
    __uint128_t sum;
    __uint128_t difference;

    if (result == NULL) {
        return 0;
    }

    sum = (__uint128_t)n * ((__uint128_t)n + 1) / 2;
    difference = sum * sum - sum;

    if (difference > UINT64_MAX) {
        return 0;
    }

    *result = (uint64_t)difference;
    return 1;
}

static int discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }

    return ch == '\n';
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[128];
    char *end;
    uintmax_t value;
    uint64_t difference;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (buffer[0] == '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    {
        size_t length = 0;

        while (length < sizeof buffer && buffer[length] != '\0' &&
               buffer[length] != '\n') {
            ++length;
        }

        if (length == sizeof buffer) {
            fprintf(stderr, "Invalid input\n");
            return 1;
        }

        if (buffer[length] != '\n' && !feof(stdin)) {
            discard_line();
            fprintf(stderr, "Invalid input\n");
            return 1;
        }
    }

    errno = 0;
    value = strtoumax(buffer, &end, 10);

    if (end == buffer || errno == ERANGE || value > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (!calculate_difference((uint64_t)value, &difference)) {
        fprintf(stderr, "Result is out of range\n");
        return 1;
    }

    printf("%" PRIu64 "\n", difference);
    return 0;
}