#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_sphere_volume(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return (4.0 / 3.0) * M_PI * pow(radius, 3.0);
}

int main(void) {
    double radius;
    double volume;
    int scan_result;

    scan_result = scanf("%lf", &radius);

    if (scan_result != 1) {
        return EXIT_FAILURE;
    }

    volume = calculate_sphere_volume(radius);

    if (volume < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.6f\n", volume);

    return EXIT_SUCCESS;
}