#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} ComplexNumber;

double getComplexNumberLength(ComplexNumber number) {
    double length = sqrt((number.real * number.real) + (number.imag * number.imag));
    return length;
}

int main() {
    ComplexNumber number;

    printf("Enter the real and imaginary part of the complex number: ");
    scanf("%lf %lf", &number.real, &number.imag);

    double length = getComplexNumberLength(number);
    printf("The length of the complex number is: %lf\n", length);
    
    return 0;
}