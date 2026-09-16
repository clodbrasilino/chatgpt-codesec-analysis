#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int find_nth_non_multiple(uint64_t n, uint64_t divisor, uint64_t *result)
{
    uint64_t quotient;
    uint64_t remainder;

    if (n == 0U || divisor <= 1U || result == NULL) {
        return 0;
    }

    quotient = (n - 1U) / (divisor - 1U);
    remainder = (n - 1U) % (divisor - 1U);

    if (quotient > (UINT64_MAX - 1U - remainder) / divisor) {
        return 0;
    }

    *result = quotient * divisor + remainder + 1U;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t divisor;
    uint64_t result;

    if (scanf("%" SCNu64 " %" SCNu64, &n, &divisor) != 2) {
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