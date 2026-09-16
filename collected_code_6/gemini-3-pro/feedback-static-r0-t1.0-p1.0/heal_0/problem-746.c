#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_sector_area(double radius, double angle_degrees) {
    if (radius < 0.0 || angle_degrees < 0.0 || angle_degrees > 360.0) {
        return -1.0;
    }
    
    return (M_PI * radius * radius) * (angle_degrees / 360.0);
}

int main(void) {
    double radius;
    double angle;
    double area;
    int result;

    result = scanf("%lf %lf", &radius, &angle);
    if (result != 2) {
        return EXIT_FAILURE;
    }

    area = calculate_sector_area(radius, angle);
    if (area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.2f\n", area);

    return EXIT_SUCCESS;
}