#include <errno.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static bool is_abundant(unsigned long long number)
{
    unsigned long long sum = 1;

    if (number < 12) {
        return false;
    }

    for (unsigned long long divisor = 2;
         divisor <= number / divisor;
         ++divisor) {
        if (number % divisor == 0) {
            unsigned long long quotient = number / divisor;

            if (sum > number - divisor) {
                return true;
            }
            sum += divisor;

            if (quotient != divisor) {
                if (sum > number - quotient) {
                    return true;
                }
                sum += quotient;
            }
        }
    }

    return sum > number;
}

int main(void)
{
    unsigned long long number;
    char extra;

    errno = 0;

    if (scanf("%llu", &number) != 1 || errno == ERANGE || number == 0) {
        return EXIT_FAILURE;
    }

    if (scanf(" %c", &extra) == 1) {
        return EXIT_FAILURE;
    }

    puts(is_abundant(number) ? "Abundant" : "Not abundant");

    return EXIT_SUCCESS;
}