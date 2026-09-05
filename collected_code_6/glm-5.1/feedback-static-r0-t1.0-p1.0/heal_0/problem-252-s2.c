#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double real;
    double imag;
} Complex;

typedef struct {
    double magnitude;
    double angle;
} Polar;

int convert_to_polar(Complex c, Polar *p) {
    if (p == NULL) {
        return -1;
    }

    p->magnitude = hypot(c.real, c.imag);

    if (p->magnitude == 0.0) {
        p->angle = 0.0;
    } else {
        if (c.real == 0.0 && c.imag == 0.0) {
            p->angle = 0.0;
        } else if (c.real < 0.0 && c.imag == 0.0) {
            p->angle = M_PI;
        } else {
            p->angle = atan2(c.imag, c.real);
        }
    }

    return 0;
}

int main(void) {
    Complex c = {3.0, 4.0};
    Polar p;

    if (convert_to_polar(c, &p) != 0) {
        return EXIT_FAILURE;
    }

    printf("Magnitude: %f\n", p.magnitude);
    printf("Angle: %f rad\n", p.angle);

    Complex c2 = {0.0, 0.0};
    Polar p2;

    if (convert_to_polar(c2, &p2) != 0) {
        return EXIT_FAILURE;
    }

    printf("Magnitude: %f\n", p2.magnitude);
    printf("Angle: %f rad\n", p2.angle);

    return EXIT_SUCCESS;
}