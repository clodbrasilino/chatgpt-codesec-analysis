#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int first_digit_of_factorial(int n)
{
    double log_sum;
    double fractional;
    int digit;
    int i;

    if (n <= 1) {
        return 1;
    }

    log_sum = 0.0;
    for (i = 2; i <= n; i++) {
        log_sum += log10((double)i);
    }

    fractional = log_sum - floor(log_sum);
    digit = (int)floor(pow(10.0, fractional));

    if (digit < 1) {
        digit = 1;
    }
    if (digit > 9) {
        digit = 9;
    }

    return digit;
}

int main(void)
{
    int n;
    int result;

    printf("Enter a non-negative integer: ");
    if (scanf("%d", &n) != 1) {
        fprintf(stderr, "Error: invalid input, expected an integer.\n");
        return EXIT_FAILURE;
    }

    if (n < 0) {
        fprintf(stderr, "Error: input must be non-negative.\n");
        return EXIT_FAILURE;
    }

    result = first_digit_of_factorial(n);
    printf("First digit of %d! is %d\n", n, result);

    return EXIT_SUCCESS;
}