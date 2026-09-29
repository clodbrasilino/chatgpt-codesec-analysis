#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int is_equilateral(double side1, double side2, double side3)
{
    const double epsilon = 1e-9;
    const double scale = fmax(side1, fmax(side2, side3));

    if (!isfinite(side1) || !isfinite(side2) || !isfinite(side3) ||
        side1 <= 0.0 || side2 <= 0.0 || side3 <= 0.0) {
        return 0;
    }

    return fabs(side1 - side2) <= epsilon * scale &&
           fabs(side2 - side3) <= epsilon * scale;
}

int main(void)
{
    double side1;
    double side2;
    double side3;

    if (scanf("%lf %lf %lf", &side1, &side2, &side3) != 3) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (is_equilateral(side1, side2, side3)) {
        puts("The triangle is equilateral.");
    } else {
        puts("The triangle is not equilateral.");
    }

    return EXIT_SUCCESS;
}