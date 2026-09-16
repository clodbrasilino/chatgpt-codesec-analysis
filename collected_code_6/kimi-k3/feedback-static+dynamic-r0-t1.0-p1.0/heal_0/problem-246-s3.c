#include <stdio.h>
#include <math.h>
#include <float.h>
#include <errno.h>
#include <stdbool.h>

double babylonian_sqrt(double x)
{
    if (x < 0.0 || isnan(x)) {
        errno = EDOM;
        return NAN;
    }
    
    if (x == 0.0 || isinf(x)) {
        return x;
    }
    
    double guess = x;
    double prev_guess;
    
    if (x < 1.0) {
        guess = 1.0;
    }
    
    do {
        prev_guess = guess;
        guess = (guess + x / guess) / 2.0;
    } while (fabs(guess - prev_guess) > DBL_EPSILON * guess);
    
    return guess;
}

int main(void)
{
    double test_values[] = {0.0, 1.0, 4.0, 16.0, 25.0, 2.0, 0.25, 100.0};
    size_t num_tests = sizeof(test_values) / sizeof(test_values[0]);
    
    for (size_t i = 0; i < num_tests; i++) {
        double result = babylonian_sqrt(test_values[i]);
        printf("sqrt(%.2f) = %.10f\n", test_values[i], result);
    }
    
    return 0;
}