#include <stdbool.h>
#include <stdio.h>

static bool is_non_prime(unsigned int number)
{
    if (number < 2U) {
        return true;
    }

    for (unsigned int divisor = 2U; divisor <= number / divisor; ++divisor) {
        if (number % divisor == 0U) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    unsigned int number;

    if (scanf("%u", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (is_non_prime(number)) {
        printf("%u is not prime\n", number);
    } else {
        printf("%u is prime\n", number);
    }

    return 0;
}