#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

double babylonian_sqrt(double value, double epsilon, int max_iterations) {
    if (value < 0) {
        errno = EDOM;
        return -1.0;
    }
    
    if (value == 0.0) {
        return 0.0;
    }
    
    if (epsilon <= 0.0) {
        errno = EINVAL;
        return -1.0;
    }
    
    if (max_iterations <= 0) {
        errno = EINVAL;
        return -1.0;
    }
    
    double guess = value;
    /* Possible weaknesses found:
     *  The scope of the variable 'previous_guess' can be reduced. [variableScope]
     */
    double previous_guess;
    int iteration = 0;
    
    do {
        previous_guess = guess;
        guess = (guess + value / guess) / 2.0;
        iteration++;
        
        if (fabs(guess - previous_guess) < epsilon) {
            return guess;
        }
        
        if (iteration >= max_iterations) {
            return guess;
        }
        
        if (guess <= 0.0 || !isfinite(guess)) {
            errno = ERANGE;
            return -1.0;
        }
    } while (1);
}

int main(int argc, char *argv[]) {
    double values[] = {0.0, 1.0, 4.0, 16.0, 25.0, 100.0, 625.0, 0.5, 2e10, 1e-10};
    int num_values = sizeof(values) / sizeof(values[0]);
    
    for (int i = 0; i < num_values; i++) {
        errno = 0;
        double result = babylonian_sqrt(values[i], 1e-10, 1000);
        
        if (errno != 0) {
            fprintf(stderr, "Error computing sqrt(%g): errno=%d\n", values[i], errno);
            continue;
        }
        
        printf("sqrt(%g) = %.12f\n", values[i], result);
    }
    
    errno = 0;
    /* Possible weaknesses found:
     *  Value stored to 'negative_result' during its initialization is never read [deadcode.DeadStores]
     *  Variable 'negative_result' is assigned a value that is never used. [unreadVariable]
     */
    double negative_result = babylonian_sqrt(-4.0, 1e-10, 1000);
    if (errno != 0) {
        fprintf(stderr, "Error computing sqrt(-4.0): errno=%d (expected EDOM)\n", errno);
    }
    
    return EXIT_SUCCESS;
}