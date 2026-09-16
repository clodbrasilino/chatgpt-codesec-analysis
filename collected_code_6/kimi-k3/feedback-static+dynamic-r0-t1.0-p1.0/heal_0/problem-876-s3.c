#include <stdio.h>
#include <stdint.h>
#include <limits.h>

static uint64_t gcd(uint64_t a, uint64_t b)
{
    while (b != 0U) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

static int lcm(uint64_t a, uint64_t b, uint64_t *result)
{
    uint64_t common_divisor;
    uint64_t quotient;

    if ((a == 0U) || (b == 0U) || (result == NULL)) {
        return -1;
    }

    common_divisor = gcd(a, b);
    quotient = a / common_divisor;

    if ((quotient != 0U) && (b > (UINT64_MAX / quotient))) {
        return -1;
    }

    *result = quotient * b;
    return 0;
}

int main(void)
{
    uint64_t num1;
    uint64_t num2;
    uint64_t result;
    int status;

    if (scanf("%llu %llu", &num1, &num2) != 2) {
        return 1;
    }

    if ((num1 == 0U) || (num2 == 0U)) {
        return 1;
    }

    status = lcm(num1, num2, &result);
    if (status != 0) {
        return 1;
    }

    if (printf("%llu\n", result) < 0) {
        return 1;
    }

    return 0;
}