#include <stdio.h>
#include <complex.h>
#include <math.h>

double get_complex_length(double complex z) {
    return cabs(z);
}

int main(void) {
    double complex z = 3.0 + 4.0 * I;
    double length = get_complex_length(z);
    if (isfinite(length)) {
        printf("%f\n", length);
    } else {
        return 1;
    }
    return 0;
}