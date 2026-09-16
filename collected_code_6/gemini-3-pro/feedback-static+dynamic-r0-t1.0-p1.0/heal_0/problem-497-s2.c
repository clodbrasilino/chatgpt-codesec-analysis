#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cone_surface_area(double radius, double height);

double calculate_cone_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return M_PI * radius * (radius + sqrt((radius * radius) + (height * height)));
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double surface_area = 0.0;
    int input_status = 0;

    input_status = scanf("%lf %lf", &radius, &height);

    if (input_status != 2) {
        return 1;
    }

    surface_area = calculate_cone_surface_area(radius, height);

    if (surface_area < 0.0) {
        return 1;
    }

    printf("%f\n", surface_area);

    return 0;
}