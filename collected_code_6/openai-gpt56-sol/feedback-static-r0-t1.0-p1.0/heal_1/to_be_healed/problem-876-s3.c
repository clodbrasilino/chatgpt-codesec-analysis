#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t gcd(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t remainder = a % b;
        a = b;
        b = remainder;
    }

    return a;
}

static int lcm(uint64_t a, uint64_t b, uint64_t *result)
{
    uint64_t quotient;

    if (a == 0U || b == 0U || result == NULL) {
        return 0;
    }

    quotient = a / gcd(a, b);

    if (quotient > UINT64_MAX / b) {
        return 0;
    }

    *result = quotient * b;
    return 1;
}

int main(void)
{
    uint64_t a;
    uint64_t b;
    uint64_t result;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64, &a, &b) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (!lcm(a, b, &result)) {
        fprintf(stderr, "Inputs must be positive and the result must fit in uint64_t\n");
        return 1;
    }

    printf("%" PRIu64 "\n", result);
    return 0;
}