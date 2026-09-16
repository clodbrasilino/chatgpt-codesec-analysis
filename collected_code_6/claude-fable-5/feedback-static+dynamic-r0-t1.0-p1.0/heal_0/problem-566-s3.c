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

int main(void)
{
    unsigned long long value = 0ULL;
    long long input = 0LL;
    int scan_result = 0;

    printf("Enter a non-negative integer: ");

    scan_result = scanf("%lld", &input);
    if (scan_result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (input < 0LL) {
        fprintf(stderr, "Error: value must be non-negative.\n");
        return EXIT_FAILURE;
    }

    value = (unsigned long long)input;

    printf("Digit sum of %llu is %llu\n", value, digit_sum(value));

    return EXIT_SUCCESS;
}