#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_of_cubes(uint64_t n, uint64_t *result)
{
    uint64_t a = n;
    uint64_t b;

    if (result == NULL) {
        return -1;
    }

    if (n == UINT64_MAX) {
        return -1;
    }

    b = n + 1U;

    if ((a & 1U) == 0U) {
        a /= 2U;
    } else {
        b /= 2U;
    }

    if (a != 0U && b > UINT64_MAX / a) {
        return -1;
    }

    a *= b;

    if (a != 0U && a > UINT64_MAX / a) {
        return -1;
    }

    *result = a * a;
    return 0;
}

int main(void)
{
    uint64_t n;
    uint64_t sum;

    if (printf("Enter n: ") < 0) {
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (sum_of_cubes(n, &sum) != 0) {
        fprintf(stderr, "Result exceeds the supported range\n");
        return EXIT_FAILURE;
    }

    if (printf("Sum: %" PRIu64 "\n", sum) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}