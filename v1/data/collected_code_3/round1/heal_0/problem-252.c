#include <stdio.h>
#include <math.h>

typedef struct Complex {
    double real;
    double imag;
} Complex;

typedef struct Polar {
    double r;
    double theta;
} Polar;

Polar toPolar(Complex c) {
    Polar p;
    p.r = sqrt(c.real * c.real + c.imag * c.imag);
    p.theta = atan2(c.imag, c.real);
    return p;
}

int main() {
    Complex c;
    printf("Enter real and imaginary parts of complex number:\n");
    scanf("%lf %lf", &c.real, &c.imag);

    Polar p = toPolar(c);

    printf("The polar coordinates are: r = %lf, theta = %lf\n", p.r, p.theta);

    return 0;
}