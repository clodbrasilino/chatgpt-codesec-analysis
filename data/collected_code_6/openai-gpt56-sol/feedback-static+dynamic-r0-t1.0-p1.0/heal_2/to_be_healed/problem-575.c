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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char trailing;
    uint64_t n;
    uint64_t divisor;
    uint64_t result;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, "%" SCNu64 " %" SCNu64 " %c",
               &n, &divisor, &trailing) != 2) {
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