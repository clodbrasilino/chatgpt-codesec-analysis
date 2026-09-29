#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static uint64_t max_exchange_sum(uint64_t n)
{
    if (n < 12U) {
        return n;
    }

    uint64_t divided_sum =
        max_exchange_sum(n / 2U) +
        max_exchange_sum(n / 3U) +
        max_exchange_sum(n / 4U);

    return divided_sum > n ? divided_sum : n;
}

int main(void)
{
    uint64_t number;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", max_exchange_sum(number));
    return EXIT_SUCCESS;
}