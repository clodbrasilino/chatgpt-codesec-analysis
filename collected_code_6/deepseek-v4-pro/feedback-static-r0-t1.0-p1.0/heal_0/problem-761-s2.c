#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_arc_length(double radius, double angle_degrees, int *error_flag) {
    double angle_radians;
    double arc_length;

    if (radius < 0.0) {
        *error_flag = 1;
        return 0.0;
    }

    if (angle_degrees < 0.0 || angle_degrees > 360.0) {
        *error_flag = 1;
        return 0.0;
    }

    angle_radians = angle_degrees * (M_PI / 180.0);
    arc_length = radius * angle_radians;

    *error_flag = 0;
    return arc_length;
}

int main(void) {
    double radius;
    double angle;
    double result;
    int error_flag = 0;

    if (scanf("%lf %lf", &radius, &angle) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = calculate_arc_length(radius, angle, &error_flag);

    if (error_flag != 0) {
        fprintf(stderr, "Invalid arguments\n");
        return EXIT_FAILURE;
    }

    printf("%.6f\n", result);
    return EXIT_SUCCESS;
}