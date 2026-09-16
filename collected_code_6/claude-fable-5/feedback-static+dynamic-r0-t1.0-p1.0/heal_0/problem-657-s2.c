#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int first_digit_of_factorial(int n)
{
    double log_sum;
    double fractional_part;
    int i;

    if (n < 0) {
        return -1;
    }

    if (n <= 1) {
        return 1;
    }

    log_sum = 0.0;
    for (i = 2; i <= n; i++) {
        log_sum += log10((double)i);
    }

    fractional_part = log_sum - floor(log_sum);

    return (int)floor(pow(10.0, fractional_part));
}

int main(void)
{
    int number;
    int result;

    printf("Enter a non-negative integer: ");

    if (scanf("%d", &number) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = first_digit_of_factorial(number);

    if (result < 0) {
        fprintf(stderr, "Error: factorial is not defined for negative numbers.\n");
        return EXIT_FAILURE;
    }

    printf("The first digit of %d! is %d\n", number, result);

    return EXIT_SUCCESS;
}