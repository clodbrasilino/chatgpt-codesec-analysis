#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TRIANGLE_INVALID,
    TRIANGLE_EQUILATERAL,
    TRIANGLE_ISOSCELES,
    TRIANGLE_SCALENE
} TriangleType;

static int nearly_equal(double a, double b)
{
    double scale = fmax(1.0, fmax(fabs(a), fabs(b)));
    return fabs(a - b) <= 1e-12 * scale;
}

static TriangleType get_triangle_type(double a, double b, double c)
{
    double sides[3] = {a, b, c};
    double temporary;

    if (!isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return TRIANGLE_INVALID;
    }

    if (sides[0] > sides[1]) {
        temporary = sides[0];
        sides[0] = sides[1];
        sides[1] = temporary;
    }

    if (sides[1] > sides[2]) {
        temporary = sides[1];
        sides[1] = sides[2];
        sides[2] = temporary;
    }

    if (sides[0] > sides[1]) {
        temporary = sides[0];
        sides[0] = sides[1];
        sides[1] = temporary;
    }

    if (sides[0] <= sides[2] - sides[1]) {
        return TRIANGLE_INVALID;
    }

    if (nearly_equal(a, b) && nearly_equal(b, c)) {
        return TRIANGLE_EQUILATERAL;
    }

    if (nearly_equal(a, b) || nearly_equal(b, c) || nearly_equal(a, c)) {
        return TRIANGLE_ISOSCELES;
    }

    return TRIANGLE_SCALENE;
}

int main(void)
{
    double a;
    double b;
    double c;
    TriangleType type;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    type = get_triangle_type(a, b, c);

    switch (type) {
        case TRIANGLE_EQUILATERAL:
            puts("Equilateral");
            break;
        case TRIANGLE_ISOSCELES:
            puts("Isosceles");
            break;
        case TRIANGLE_SCALENE:
            puts("Scalene");
            break;
        case TRIANGLE_INVALID:
            puts("Not a triangle");
            break;
        default:
            fputs("Unexpected triangle type\n", stderr);
            return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}