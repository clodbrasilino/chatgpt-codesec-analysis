#include <stdio.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

typedef struct {
    double magnitude;
    double angle;
} Polar;

Polar to_polar(Complex c) {
    Polar p;
    p.magnitude = sqrt(c.real * c.real + c.imag * c.imag);
    p.angle = atan2(c.imag, c.real);
    return p;
}

int main(void) {
    Complex c = {3.0, 4.0};
    Polar p = to_polar(c);
    printf("Magnitude: %.2f\n", p.magnitude);
    printf("Angle: %.2f radians\n", p.angle);
    return 0;
}