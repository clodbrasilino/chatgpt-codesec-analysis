#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

static double babylonian_sqrt(double value, int *error)
{
    double guess;
    double previous;
    const double tolerance = DBL_EPSILON * 4.0;

    if (error == NULL) {
        return 0.0;
    }

    if (value < 0.0 || isnan(value) || isinf(value)) {
        *error = 1;
        return 0.0;
    }

    *error = 0;

    if (value == 0.0) {
        return 0.0;
    }

    guess = value / 2.0;
    if (guess == 0.0) {
        guess = value;
    }

    do {
        previous = guess;
        guess = (guess + value / guess) / 2.0;
    } while (fabs(guess - previous) > tolerance * guess);

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
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    result = babylonian_sqrt(input, &error);
    if (error != 0) {
        fprintf(stderr, "Error: cannot compute square root of the given value.\n");
        return EXIT_FAILURE;
    }

    printf("Square root of %f is approximately %f\n", input, result);

    return EXIT_SUCCESS;
}