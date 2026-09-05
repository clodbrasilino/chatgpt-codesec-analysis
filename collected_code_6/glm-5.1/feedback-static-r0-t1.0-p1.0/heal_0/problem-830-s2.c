#include <stdio.h>
#include <math.h>
#include <float.h>

double round_up_digits(double num, int digits) {
    if (digits < 0) {
        return NAN;
    }
    if (digits > DBL_MAX_10_EXP) {
        return num;
    }
    if (num == 0.0) {
        return 0.0;
    }
    double factor = pow(10.0, digits);
    double shifted = num * factor;
    double floored = floor(shifted);
    if (shifted != floored) {
        floored += 1.0;
    }
    return floored / factor;
}

int main(void) {
    printf("%f\n", round_up_digits(3.1415, 2));
    printf("%f\n", round_up_digits(3.1400, 2));
    printf("%f\n", round_up_digits(-3.1415, 2));
    printf("%f\n", round_up_digits(123.456, 0));
    printf("%f\n", round_up_digits(0.0, 3));
    return 0;
}