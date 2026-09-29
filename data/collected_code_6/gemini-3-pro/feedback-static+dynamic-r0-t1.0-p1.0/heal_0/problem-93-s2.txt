#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_power(double base, long long exponent) {
    if (base == 0.0 && exponent == 0) {
        return 1.0;
    }
    if (base == 0.0 && exponent < 0) {
        return INFINITY;
    }
    if (exponent == 0) {
        return 1.0;
    }

    long long abs_exp = exponent < 0 ? -exponent : exponent;
    double result = 1.0;
    double current_base = base;

    while (abs_exp > 0) {
        if (abs_exp % 2 == 1) {
            result *= current_base;
        }
        current_base *= current_base;
        abs_exp /= 2;
    }

    if (exponent < 0) {
        return 1.0 / result;
    }
    
    return result;
}

int main(void) {
    double base = 2.5;
    long long exponent = 3;
    double result;

    result = calculate_power(base, exponent);
    printf("%f\n", result);

    base = 2.0;
    exponent = -3;
    result = calculate_power(base, exponent);
    printf("%f\n", result);

    base = 0.0;
    exponent = -1;
    result = calculate_power(base, exponent);
    printf("%f\n", result);

    return 0;
}