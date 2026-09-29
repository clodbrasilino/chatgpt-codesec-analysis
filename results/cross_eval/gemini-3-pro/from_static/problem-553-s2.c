#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tuple_to_float(int whole, int fractional) {
    if (fractional < 0) {
        return NAN;
    }

    double frac_part = (double)fractional;
    while (frac_part >= 1.0) {
        frac_part /= 10.0;
    }

    if (whole < 0) {
        return (double)whole - frac_part;
    }

    return (double)whole + frac_part;
}

int main(void) {
    int whole_part = 42;
    int fractional_part = 567;
    
    double result = tuple_to_float(whole_part, fractional_part);
    
    if (isnan(result)) {
        printf("Error: Invalid fractional part.\n");
        return EXIT_FAILURE;
    }
    
    printf("Result: %f\n", result);
    
    return EXIT_SUCCESS;
}