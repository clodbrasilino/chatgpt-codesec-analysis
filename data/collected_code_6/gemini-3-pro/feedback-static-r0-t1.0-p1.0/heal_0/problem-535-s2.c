#include <stdio.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cylinder_surface_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

int main(void) {
    double radius = 5.0;
    double area;

    area = calculate_cylinder_surface_area(radius);

    if (area < 0.0) {
        fprintf(stderr, "Error: Invalid radius provided.\n");
        return 1;
    }

    printf("The top/bottom surface area of the cylinder is: %.2f\n", area);

    return 0;
}