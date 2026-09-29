#include <stdio.h>
#include <stdlib.h>

int digit_sum_difference(long long number);

int digit_sum_difference(long long number)
{
    int even_sum = 0;
    int odd_sum = 0;

    if (number < 0) {
        number = -number;
    }

    if (number == 0) {
        return 0;
    }

    while (number > 0) {
        int digit = (int)(number % 10);
        if ((digit % 2) == 0) {
            even_sum += digit;
        } else {
            odd_sum += digit;
        }
        number /= 10;
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