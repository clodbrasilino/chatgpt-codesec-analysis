#include <stdio.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

double calculate_lateral_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0; 
    }
    return 2.0 * PI * radius * height;
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double lateral_area = 0.0;

    if (scanf("%lf %lf", &radius, &height) != 2) {
        return EXIT_FAILURE;
    }

    lateral_area = calculate_lateral_surface_area(radius, height);

    if (lateral_area < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%.6f\n", lateral_area);

    return EXIT_SUCCESS;
}