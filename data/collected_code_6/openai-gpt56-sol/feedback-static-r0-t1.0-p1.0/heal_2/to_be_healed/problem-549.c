#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_fifth_powers_of_odds(uint64_t n, uint64_t *result)
{
    uint64_t sum = 0;

    if (result == NULL || n > UINT64_C(1324)) {
        return 0;
    }

    for (uint64_t i = 0; i < n; ++i) {
        uint64_t odd = (UINT64_C(2) * i) + UINT64_C(1);
        uint64_t square = odd * odd;
        uint64_t fourth = square * square;
        uint64_t fifth = fourth * odd;

        if (UINT64_MAX - sum < fifth) {
            return 0;
        }

        sum += fifth;
    }

    *result = sum;
    return 1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[128];
    char *end;
    uintmax_t parsed;
    uint64_t n;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    parsed = strtoumax(input, &end, 10);

    if (end == input || errno == ERANGE || parsed > UINT64_MAX) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    n = (uint64_t)parsed;

    if (!sum_fifth_powers_of_odds(n, &result)) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}