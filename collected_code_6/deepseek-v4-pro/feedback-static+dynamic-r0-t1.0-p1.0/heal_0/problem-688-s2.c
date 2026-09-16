#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

double complex_length(Complex c) {
    return sqrt(c.real * c.real + c.imag * c.imag);
}

int main(void) {
    Complex z;
    
    z.real = 3.0;
    z.imag = 4.0;
    
    printf("Length: %.2f\n", complex_length(z));
    
    z.real = 1.0;
    z.imag = -1.0;
    
    printf("Length: %.2f\n", complex_length(z));
    
    z.real = 0.0;
    z.imag = 0.0;
    
    printf("Length: %.2f\n", complex_length(z));
    
    return 0;
}