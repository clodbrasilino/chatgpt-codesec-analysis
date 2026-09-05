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

Polar complex_to_polar(Complex c) {
    Polar p;
    p.magnitude = hypot(c.real, c.imag);
    p.angle = atan2(c.imag, c.real);
    return p;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <real> <imaginary>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_real;
    char *endptr_imag;
    double real_part = strtod(argv[1], &endptr_real);
    double imag_part = strtod(argv[2], &endptr_imag);

    if (endptr_real == argv[1] || *endptr_real != '\0' || endptr_imag == argv[2] || *endptr_imag != '\0') {
        fprintf(stderr, "Invalid input: arguments must be valid numbers\n");
        return EXIT_FAILURE;
    }

    Complex c = {real_part, imag_part};
    Polar p = complex_to_polar(c);

    printf("Magnitude: %.6f\n", p.magnitude);
    printf("Angle (radians): %.6f\n", p.angle);

    return EXIT_SUCCESS;
}