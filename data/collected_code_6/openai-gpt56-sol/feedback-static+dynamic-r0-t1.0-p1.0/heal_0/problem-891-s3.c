#include <stdio.h>

static unsigned int digit_count(long long number)
{
    unsigned int count = 1U;

    while (number <= -10LL || number >= 10LL) {
        number /= 10LL;
        ++count;
    }

    return count;
}

static int have_same_digit_count(long long first, long long second)
{
    return digit_count(first) == digit_count(second);
}

int main(void)
{
    long long first;
    long long second;

    if (scanf("%lld %lld", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (have_same_digit_count(first, second)) {
        puts("The numbers have the same number of digits.");
    } else {
        puts("The numbers do not have the same number of digits.");
    }

    return 0;
}