#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fourth_powers_even(uint32_t n, uint64_t *result)
{
    const uint32_t limit = 249U;
    uint64_t sum = 0U;

    if (result == NULL || n > limit) {
        return -1;
    }

    for (uint64_t i = 1U; i <= (uint64_t)n; ++i) {
        const uint64_t even = 2U * i;
        const uint64_t square = even * even;
        sum += square * square;
    }

    *result = sum;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[64];
    char *end;
    uintmax_t value;
    uint64_t sum;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(input, &end, 10);

    if (errno == ERANGE || end == input || value > UINT32_MAX) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' || *end == '\n' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (sum_fourth_powers_even((uint32_t)value, &sum) != 0) {
        fputs("Input is out of range\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", sum);
    return 0;
}