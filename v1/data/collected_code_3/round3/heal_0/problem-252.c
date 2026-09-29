#include <stdio.h>
#include <math.h>

typedef struct Complex {
    double real;
    double imag;
} Complex;

typedef struct Polar {
    double magnitude;
    double angle;
} Polar;

Polar complexToPolar(Complex c) {
    Polar p;
    p.magnitude = sqrt(c.real * c.real + c.imag * c.imag);
    p.angle = atan2(c.imag, c.real);
    return p;
}

int main() {
    Complex c;
    c.real = 3.0;
    c.imag = 4.0;

    Polar p = complexToPolar(c);

    printf("Magnitude: %f, Angle: %f\n", p.magnitude, p.angle);

    return 0;
}