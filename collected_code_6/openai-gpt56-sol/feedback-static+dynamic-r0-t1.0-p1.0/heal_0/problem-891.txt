#include <stdio.h>

static unsigned int count_digits(long long number)
{
    unsigned int count = 1U;

    while (number <= -10 || number >= 10) {
        number /= 10;
        ++count;
    }

    return count;
}

static int have_same_number_of_digits(long long first, long long second)
{
    return count_digits(first) == count_digits(second);
}

int main(void)
{
    long long first;
    long long second;

    if (scanf("%lld %lld", &first, &second) != 2) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(have_same_number_of_digits(first, second) ? "Yes" : "No");

    return 0;
}