#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int sum_even_squares(uint64_t n, uint64_t *result)
{
    const uint64_t max_n = UINT64_C(2097151);
    uint64_t a;
    uint64_t b;
    uint64_t c;

    if (result == NULL || n > max_n) {
        return 0;
    }

    a = n;
    b = n + UINT64_C(1);
    c = (UINT64_C(2) * n) + UINT64_C(1);

    if ((a % UINT64_C(3)) == 0U) {
        a /= UINT64_C(3);
    } else if ((b % UINT64_C(3)) == 0U) {
        b /= UINT64_C(3);
    } else {
        c /= UINT64_C(3);
    }

    if ((a % UINT64_C(2)) == 0U) {
        a /= UINT64_C(2);
    } else {
        b /= UINT64_C(2);
    }

    *result = UINT64_C(4) * a * b * c;
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &n) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!sum_even_squares(n, &result)) {
        fputs("Input is too large\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}