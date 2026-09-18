#include <math.h>
#include <complex.h>
#include <stdio.h>

double get_complex_length(double complex num) {
    return sqrt(pow(creal(num), 2) + pow(cimag(num), 2));
}

int main() {
    double complex num = 3 + 4*I;

    double length = get_complex_length(num);
    printf("The length of the complex number is %.2f\n", length);

    return 0;
}