#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static uint64_t highest_power_of_two(uint64_t number)
{
    if (number == 0U) {
        return 0U;
    }

    uint64_t result = 1U;

    while (result <= number / 2U) {
        result *= 2U;
    }

    return result;
}

int main(void)
{
    uint64_t number = 0U;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%" PRIu64 "\n", highest_power_of_two(number));
    return 0;
}