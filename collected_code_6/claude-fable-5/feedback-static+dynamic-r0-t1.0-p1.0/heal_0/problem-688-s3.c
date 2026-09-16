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
        return NAN;
    }
    return hypot(c->real, c->imag);
}

int main(void)
{
    Complex c;
    double length;

    printf("Enter real part: ");
    if (scanf("%lf", &c.real) != 1) {
        fprintf(stderr, "Invalid input for real part\n");
        return EXIT_FAILURE;
    }

    printf("Enter imaginary part: ");
    if (scanf("%lf", &c.imag) != 1) {
        fprintf(stderr, "Invalid input for imaginary part\n");
        return EXIT_FAILURE;
    }

    length = complex_length(&c);
    if (isnan(length)) {
        fprintf(stderr, "Failed to compute length\n");
        return EXIT_FAILURE;
    }

    printf("Length of complex number (%.6f + %.6fi) = %.6f\n",
           c.real, c.imag, length);

    return EXIT_SUCCESS;
}