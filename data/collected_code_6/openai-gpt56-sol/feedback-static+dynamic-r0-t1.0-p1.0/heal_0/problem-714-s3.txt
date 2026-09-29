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

    if (scanf("%" SCNu64, &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%zu\n", count_distinct_prime_power_factors(number));
    return 0;
}