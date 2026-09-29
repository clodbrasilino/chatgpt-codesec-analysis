#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double babylonian_sqrt(double n);

double babylonian_sqrt(double n) {
    double guess;
    double prev_guess;
    double tolerance = 1e-9;

    if (n < 0.0) {
        return -1.0;
    }
    if (n == 0.0) {
        return 0.0;
    }

    guess = n / 2.0;
    prev_guess = 0.0;

    while (fabs(guess - prev_guess) > tolerance) {
        prev_guess = guess;
        guess = 0.5 * (guess + (n / guess));
    }

    return guess;
}

int main(void) {
    double numbers[] = {25.0, 2.0, 0.0, -9.0, 10000.0};
    size_t num_elements = sizeof(numbers) / sizeof(numbers[0]);
    size_t i;
    double result;

    for (i = 0; i < num_elements; i++) {
        result = babylonian_sqrt(numbers[i]);
        if (result < 0.0) {
            fprintf(stderr, "Error: Cannot compute square root of a negative number (%.2f)\n", numbers[i]);
        } else {
            printf("Square root of %.2f is %.5f\n", numbers[i], result);
        }
    }

    return EXIT_SUCCESS;
}