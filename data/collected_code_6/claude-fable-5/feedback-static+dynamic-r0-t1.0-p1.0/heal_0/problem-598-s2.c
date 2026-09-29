#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

static int count_digits(long long num)
{
    int count = 0;

    if (num == 0) {
        return 1;
    }

    while (num != 0) {
        num /= 10;
        count++;
    }

    return count;
}

static bool safe_power(long long base, int exp, long long *out)
{
    long long result = 1;
    int i;

    for (i = 0; i < exp; i++) {
        if (base != 0 && result > LLONG_MAX / base) {
            return false;
        }
        result *= base;
    }

    *out = result;
    return true;
}

static bool is_armstrong(long long num)
{
    long long original;
    long long sum = 0;
    int digits;

    if (num < 0) {
        return false;
    }

    original = num;
    digits = count_digits(num);

    while (num != 0) {
        long long digit = num % 10;
        long long power;

        if (!safe_power(digit, digits, &power)) {
            return false;
        }

        if (sum > LLONG_MAX - power) {
            return false;
        }

        sum += power;
        num /= 10;
    }

    return sum == original;
}

int main(void)
{
    long long num;
    int result;

    printf("Enter a non-negative integer: ");

    result = scanf("%lld", &num);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return 1;
    }

    if (num < 0) {
        fprintf(stderr, "Error: number must be non-negative.\n");
        return 1;
    }

    if (is_armstrong(num)) {
        printf("%lld is an Armstrong number.\n", num);
    } else {
        printf("%lld is not an Armstrong number.\n", num);
    }

    return 0;
}