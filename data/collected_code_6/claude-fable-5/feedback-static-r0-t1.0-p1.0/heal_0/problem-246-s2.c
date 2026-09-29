#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double babylonian_sqrt(double value, int *error);

double babylonian_sqrt(double value, int *error)
{
    double guess;
    double previous;
    const double epsilon = 1e-12;

    if (error == NULL) {
        return 0.0;
    }

    if (isnan(value) || isinf(value) || value < 0.0) {
        *error = 1;
        return 0.0;
    }

    *error = 0;

    if (value == 0.0) {
        return 0.0;
    }

    guess = value > 1.0 ? value / 2.0 : 1.0;

    do {
        previous = guess;
        guess = 0.5 * (guess + value / guess);
    } while (fabs(guess - previous) > epsilon * fabs(guess));

    return guess;
}

int main(void)
{
    double input;
    double result;
    int error;
    int scan_status;

    printf("Enter a non-negative number: ");
    scan_status = scanf("%lf", &input);

    if (scan_status != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    result = babylonian_sqrt(input, &error);

    if (error != 0) {
        fprintf(stderr, "Cannot compute square root of the given value.\n");
        return EXIT_FAILURE;
    }

    printf("Square root of %.10f is %.10f\n", input, result);

    return EXIT_SUCCESS;
}