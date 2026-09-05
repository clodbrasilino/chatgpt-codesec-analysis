#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

double babylonian_sqrt(double n) {
    if (n < 0.0) {
        return NAN;
    }
    if (n == 0.0) {
        return 0.0;
    }
    
    double x = n;
    /* Possible weaknesses found:
     *  The scope of the variable 'prev' can be reduced. [variableScope]
     *  Variable 'prev' is assigned a value that is never used. [unreadVariable]
     */
    double prev = 0.0;
    
    while (1) {
        prev = x;
        x = 0.5 * (x + n / x);
        
        if (fabs(x - prev) <= DBL_EPSILON * fmax(x, prev)) {
            break;
        }
        
        if (x == prev) {
            break;
        }
    }
    
    return x;
}

int main(int argc, char *argv[]) {
    double val = 25.0;
    double result = babylonian_sqrt(val);
    
    if (isnan(result)) {
        fprintf(stderr, "Invalid input for square root\n");
        return EXIT_FAILURE;
    }
    
    printf("Square root of %.6f is %.6f\n", val, result);
    
    val = -4.0;
    result = babylonian_sqrt(val);
    
    if (isnan(result)) {
        fprintf(stderr, "Invalid input for square root\n");
    } else {
        printf("Square root of %.6f is %.6f\n", val, result);
    }
    
    return EXIT_SUCCESS;
}