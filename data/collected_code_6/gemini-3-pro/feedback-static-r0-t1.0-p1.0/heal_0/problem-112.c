#include <stdio.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cylinder_perimeter(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * ((2.0 * M_PI * radius) + height);
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double perimeter = 0.0;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        return EXIT_FAILURE;
    }

    perimeter = calculate_cylinder_perimeter(radius, height);
    if (perimeter < 0.0) {
        return EXIT_FAILURE;
    }

    if (printf("%.6f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}