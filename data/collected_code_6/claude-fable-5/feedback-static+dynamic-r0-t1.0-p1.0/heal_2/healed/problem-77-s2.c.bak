#include <stdio.h>
#include <stdlib.h>

int digit_sum_difference(long long number);

int digit_sum_difference(long long number)
{
    int even_sum = 0;
    int odd_sum = 0;
    unsigned long long magnitude;

    if (number < 0) {
        magnitude = (unsigned long long)(-(number + 1)) + 1ULL;
    } else {
        magnitude = (unsigned long long)number;
    }

    if (magnitude == 0ULL) {
        return 0;
    }

    while (magnitude > 0ULL) {
        const int digit = (int)(magnitude % 10ULL);
        if ((digit % 2) == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        magnitude /= 10ULL;
    }

    return even_sum - odd_sum;
}

int main(void)
{
    long long input = 0;
    int result;

    printf("Enter an integer: ");
    if (scanf("%lld", &input) != 1) {
        fprintf(stderr, "Error: invalid input\n");
        return EXIT_FAILURE;
    }

    result = digit_sum_difference(input);
    printf("Difference between sum of even and odd digits: %d\n", result);

    return EXIT_SUCCESS;
}