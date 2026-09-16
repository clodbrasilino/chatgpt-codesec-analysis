#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

double complex_length(Complex c) {
    return hypot(c.real, c.imag);
}

double complex_length_squared(Complex c) {
    return c.real * c.real + c.imag * c.imag;
}

int main(void) {
    Complex num = {3.0, 4.0};
    double length = complex_length(num);
    double length_sq = complex_length_squared(num);
    
    printf("Complex number: %.2f + %.2fi\n", num.real, num.imag);
    printf("Length: %.2f\n", length);
    printf("Length squared: %.2f\n", length_sq);
    printf("Verification: sqrt(%.2f) = %.2f\n", length_sq, sqrt(length_sq));
    
    Complex zero = {0.0, 0.0};
    printf("Zero length: %.2f\n", complex_length(zero));
    
    Complex negative = {-3.0, -4.0};
    printf("Negative components length: %.2f\n", complex_length(negative));
    
    return 0;
}