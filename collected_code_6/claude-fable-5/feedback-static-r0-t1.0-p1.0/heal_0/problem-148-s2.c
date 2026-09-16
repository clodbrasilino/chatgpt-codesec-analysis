#include <stdio.h>
#include <stdlib.h>

static unsigned long long digit_sum(unsigned long long n)
{
    unsigned long long sum = 0ULL;

    while (n > 0ULL) {
        sum += n % 10ULL;
        n /= 10ULL;
    }

    return sum;
}

static unsigned long long max_split_digit_sum(unsigned long long n)
{
    unsigned long long nines = 0ULL;

    if (n < 10ULL) {
        return digit_sum(n);
    }

    while (nines * 10ULL + 9ULL <= n) {
        nines = nines * 10ULL + 9ULL;
    }

    return digit_sum(nines) + digit_sum(n - nines);
}

int main(void)
{
    unsigned long long n = 0ULL;
    int result = 0;

    printf("Enter a non-negative number: ");

    result = scanf("%llu", &n);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum digit sum of two parts: %llu\n", max_split_digit_sum(n));

    return EXIT_SUCCESS;
}