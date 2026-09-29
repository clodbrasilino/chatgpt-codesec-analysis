#include <stdio.h>
#include <stdlib.h>

static unsigned long long odd_fourth_power_sum(unsigned int n)
{
    unsigned long long sum = 0ULL;
    unsigned int i;

    for (i = 1U; i <= n; i++) {
        unsigned long long odd = (unsigned long long)(2U * i - 1U);
        sum += odd * odd * odd * odd;
    }

    return sum;
}

int main(void)
{
    unsigned int n;
    unsigned long long result;

    printf("Enter n: ");
    if (scanf("%u", &n) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (n > 92681U) {
        fprintf(stderr, "Input too large, would cause overflow\n");
        return EXIT_FAILURE;
    }

    result = odd_fourth_power_sum(n);
    printf("Sum of fourth powers of first %u odd natural numbers: %llu\n", n, result);

    return EXIT_SUCCESS;
}