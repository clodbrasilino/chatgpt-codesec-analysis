#include <stdio.h>
#include <math.h>

double cylinder_lateral_surface_area(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius * height;
}

int main(void) {
    double radius = 0.0;
    double height = 0.0;
    double result = 0.0;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return 1;
    }

    result = cylinder_lateral_surface_area(radius, height);
    if (result < 0.0) {
        fprintf(stderr, "Invalid dimensions: radius and height must be non-negative\n");
        return 1;
    }

    printf("Lateral surface area: %.6f\n", result);
    return 0;
}