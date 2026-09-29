#include <stdio.h>

int even_odd_digit_sum_difference(long long number)
{
    unsigned long long value;
    int even_sum = 0;
    int odd_sum = 0;

    if (number < 0) {
        value = 0ULL - (unsigned long long)number;
    } else {
        value = (unsigned long long)number;
    }

    do {
        int digit = (int)(value % 10ULL);

        if (digit % 2 == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }

        value /= 10ULL;
    } while (value != 0ULL);

    return even_sum - odd_sum;
}

int main(void)
{
    long long number;

    if (scanf("%lld", &number) != 1) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    printf("%d\n", even_odd_digit_sum_difference(number));
    return 0;
}