#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

double getLength(Complex c) {
    return sqrt(c.real * c.real + c.imag * c.imag);
}

int main() {
    Complex c;
    c.real = 3.0;
    c.imag = 4.0;
    double length = getLength(c);
    printf("Length of the complex number is: %f\n", length);
    return 0;
}