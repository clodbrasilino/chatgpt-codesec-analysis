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

Polar complex_to_polar(Complex c) {
    Polar p;
    p.magnitude = sqrt((c.real * c.real) + (c.imag * c.imag));
    p.angle = atan2(c.imag, c.real);
    return p;
}

int main(void) {
    Complex c;
    Polar p;
    int items_read;

    items_read = scanf("%lf %lf", &c.real, &c.imag);
    
    if (items_read != 2) {
        fprintf(stderr, "Error: Invalid input.\n");
        return 1;
    }

    p = complex_to_polar(c);

    printf("%.4f %.4f\n", p.magnitude, p.angle);

    return 0;
}