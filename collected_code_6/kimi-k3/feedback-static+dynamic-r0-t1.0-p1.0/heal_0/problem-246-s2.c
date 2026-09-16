#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>

static double babylonian_sqrt(double x)
{
    if (x < 0.0 || isnan(x)) {
        errno = EDOM;
        return NAN;
    }
    
    if (x == 0.0 || isinf(x)) {
        return x;
    }
    
    double guess = x > 1.0 ? x : 1.0;
    double prev_guess = 0.0;
    
    while (fabs(guess - prev_guess) > DBL_EPSILON * guess) {
        prev_guess = guess;
        guess = (guess + x / guess) * 0.5;
    }
    
    return guess;
}

int main(void)
{
    double test_values[] = {0.0, 1.0, 4.0, 2.0, 16.0, 25.0, 0.25, 100.0};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        errno = 0;
        double result = babylonian_sqrt(test_values[i]);
        
        if (errno == EDOM) {
            fprintf(stderr, "Error: Invalid input %.2f\n", test_values[i]);
        } else {
            printf("sqrt(%.2f) = %.15f\n", test_values[i], result);
        }
    }
    
    errno = 0;
    double negative_result = babylonian_sqrt(-1.0);
    if (errno == EDOM) {
        fprintf(stderr, "Error: Cannot compute square root of negative number\n");
    }
    
    return EXIT_SUCCESS;
}