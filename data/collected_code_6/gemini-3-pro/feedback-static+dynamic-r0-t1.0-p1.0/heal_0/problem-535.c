#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double calculate_cylinder_base_area(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return M_PI * radius * radius;
}

int main(void) {
    double radius = 0.0;
    double area = 0.0;
    int result = 0;

    printf("Enter the radius of the cylinder: ");
    result = scanf("%lf", &radius);

    if (result != 1) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    area = calculate_cylinder_base_area(radius);

    if (area < 0.0) {
        fprintf(stderr, "Error: Radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("The top/bottom surface area of the cylinder is: %.6lf\n", area);

    return EXIT_SUCCESS;
}