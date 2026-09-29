#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

static size_t count_distinct_prime_power_factors(uint64_t number)
{
    size_t count = 0;

    if (number < 2) {
        return 0;
    }

    if (number % 2 == 0) {
        ++count;
        do {
            number /= 2;
        } while (number % 2 == 0);
    }

    for (uint64_t divisor = 3; divisor <= number / divisor; divisor += 2) {
        if (number % divisor == 0) {
            ++count;
            do {
                number /= divisor;
            } while (number % divisor == 0);
        }
    }

    if (number > 1) {
        ++count;
    }

    return count;
}

int main(void)
{
    uint64_t number;

    /* Possible weaknesses found:
     * Flawfinder scanf: The scanf() family's %s operation, without a limit specification, permits buffer overflows (CWE-120, CWE-20). Specify a limit to %s, or use a different input function. If the scanf format is influenceable by an attacker, it's exploitable. (risk 4, buffer)
     */
    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%zu\n", count_distinct_prime_power_factors(number));
    return 0;
}