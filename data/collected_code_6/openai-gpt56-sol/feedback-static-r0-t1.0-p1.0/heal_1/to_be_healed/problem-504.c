#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_sum(uint64_t n, uint64_t *result)
{
    uint64_t a;
    uint64_t b;

    if (result == NULL || n > 92681U) {
        return 0;
    }

    if ((n & 1U) == 0U) {
        a = n / 2U;
        b = n + 1U;
    } else {
        a = n;
        b = (n + 1U) / 2U;
    }

    *result = (a * b) * (a * b);
    return 1;
}

int main(void)
{
    uint64_t n;
    uint64_t result;
    int input_status;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    input_status = scanf("%" SCNu64, &n);
    if (input_status != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!cube_sum(n, &result)) {
        fputs("Input is out of range\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", result);
    return EXIT_SUCCESS;
}