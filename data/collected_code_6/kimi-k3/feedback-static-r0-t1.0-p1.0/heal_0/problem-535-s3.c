#include <stdio.h>
#include <math.h>

double cylinder_surface_area(double radius) {
    return M_PI * radius * radius;
}

int main(void) {
    double radius;
    int scan_result;

    printf("Enter the radius of the cylinder: ");
    scan_result = scanf("%lf", &radius);

    if (scan_result != 1) {
        fprintf(stderr, "Invalid input. Please enter a numeric value.\n");
        return 1;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Radius must be non-negative.\n");
        return 1;
    }

    printf("Top/Bottom surface area: %.6f\n", cylinder_surface_area(radius));

    return 0;
}