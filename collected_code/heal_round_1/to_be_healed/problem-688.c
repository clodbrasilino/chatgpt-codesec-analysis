#include <stdio.h>
 /* Possible weaknesses found:
  *  include '<math.h>' or provide a declaration of 'sqrt'
  */

typedef struct {
    double real;
    double imag;
} ComplexNumber;

double getComplexNumberLength(ComplexNumber number) {
    /* Possible weaknesses found:
     *  incompatible implicit declaration of built-in function 'sqrt' [-Wbuiltin-declaration-mismatch]
     *  implicit declaration of function 'sqrt' [-Wimplicit-function-declaration]
     *  include '<math.h>' or provide a declaration of 'sqrt'
     */
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