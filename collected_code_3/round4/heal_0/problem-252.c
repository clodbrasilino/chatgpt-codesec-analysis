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
    c.real = 3.0;
    c.imag = 4.0;

    Polar p = toPolar(c);

    printf("The polar coordinates are: r = %.2f, theta = %.2f\n", p.r, p.theta);

    return 0;
}