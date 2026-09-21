#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static int sum_of_proper_divisors(uint64_t number, uint64_t *sum)
{
    uint64_t result = 1U;

    if (sum == NULL || number == 0U) {
        return 0;
    }

    if (number == 1U) {
        *sum = 0U;
        return 1;
    }

    for (uint64_t divisor = 2U; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0U) {
            uint64_t quotient = number / divisor;

            if (UINT64_MAX - result < divisor) {
                return 0;
            }
            result += divisor;

            if (quotient != divisor) {
                if (UINT64_MAX - result < quotient) {
                    return 0;
                }
                result += quotient;
            }
        }
    }

    *sum = result;
    return 1;
}

int main(void)
{
    uint64_t first;
    uint64_t second;
    uint64_t first_sum;
    uint64_t second_sum;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64 " %" SCNu64, &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!sum_of_proper_divisors(first, &first_sum) ||
        !sum_of_proper_divisors(second, &second_sum)) {
        fputs("Unable to calculate divisor sums\n", stderr);
        return 1;
    }

    puts(first_sum == second_sum ? "Same" : "Not same");
    return 0;
}