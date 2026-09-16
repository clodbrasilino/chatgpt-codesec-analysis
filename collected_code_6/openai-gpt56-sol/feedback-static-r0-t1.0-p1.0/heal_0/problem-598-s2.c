#include <stdio.h>

static unsigned long long power_ull(unsigned int base, unsigned int exponent)
{
    unsigned long long result = 1ULL;

    while (exponent > 0U) {
        result *= base;
        --exponent;
    }

    return result;
}

static int is_armstrong(unsigned long long number)
{
    unsigned long long temp = number;
    unsigned long long sum = 0ULL;
    unsigned int digits = 0U;

    do {
        ++digits;
        temp /= 10ULL;
    } while (temp != 0ULL);

    temp = number;

    do {
        unsigned int digit = (unsigned int)(temp % 10ULL);
        unsigned long long term = power_ull(digit, digits);

        if (sum > number || term > number - sum) {
            return 0;
        }

        sum += term;
        temp /= 10ULL;
    } while (temp != 0ULL);

    return sum == number;
}

int main(void)
{
    unsigned long long number;
    char trailing;

    if (scanf("%llu", &number) != 1) {
        return 1;
    }

    if (scanf(" %c", &trailing) == 1) {
        return 1;
    }

    if (is_armstrong(number) != 0) {
        printf("%llu is an Armstrong number.\n", number);
    } else {
        printf("%llu is not an Armstrong number.\n", number);
    }

    return 0;
}