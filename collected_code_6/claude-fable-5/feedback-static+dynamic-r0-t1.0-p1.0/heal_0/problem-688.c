#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

double complex_length(const Complex *c)
{
    if (c == NULL) {
        return -1.0;
    }
    return hypot(c->real, c->imag);
}

int main(void)
{
    Complex num;
    double length;

    printf("Enter the real part: ");
    if (scanf("%lf", &num.real) != 1) {
        fprintf(stderr, "Invalid input for real part\n");
        return EXIT_FAILURE;
    }

    printf("Enter the imaginary part: ");
    if (scanf("%lf", &num.imag) != 1) {
        fprintf(stderr, "Invalid input for imaginary part\n");
        return EXIT_FAILURE;
    }

    length = complex_length(&num);
    if (length < 0.0) {
        fprintf(stderr, "Error computing length\n");
        return EXIT_FAILURE;
    }

    printf("The length of the complex number (%f + %fi) is %f\n",
           num.real, num.imag, length);

    return EXIT_SUCCESS;
}