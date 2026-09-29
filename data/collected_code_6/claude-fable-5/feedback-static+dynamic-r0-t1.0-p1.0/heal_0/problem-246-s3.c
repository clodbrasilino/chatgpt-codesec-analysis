#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double babylonian_sqrt(double value, double tolerance)
{
    double guess;
    double next;

    if (value < 0.0) {
        return -1.0;
    }

    if (value == 0.0) {
        return 0.0;
    }

    guess = value / 2.0;
    if (guess <= 0.0) {
        guess = 1.0;
    }

    for (;;) {
        next = 0.5 * (guess + value / guess);
        if (fabs(next - guess) <= tolerance * fabs(next)) {
            break;
        }
        guess = next;
    }

    return next;
}

int main(void)
{
    double input;
    double result;
    int status;

    printf("Enter a non-negative number: ");
    status = scanf("%lf", &input);
    if (status != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (input < 0.0) {
        fprintf(stderr, "Error: cannot compute square root of a negative number.\n");
        return EXIT_FAILURE;
    }

    result = babylonian_sqrt(input, 1e-12);
    if (result < 0.0) {
        fprintf(stderr, "Error: computation failed.\n");
        return EXIT_FAILURE;
    }

    printf("Square root of %.10f is %.10f\n", input, result);
    return EXIT_SUCCESS;
}