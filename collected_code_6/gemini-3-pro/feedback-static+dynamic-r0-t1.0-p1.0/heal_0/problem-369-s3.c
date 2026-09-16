#include <stdio.h>
#include <stdlib.h>

double calculate_lateral_surface_area(double length, double width, double height);

double calculate_lateral_surface_area(double length, double width, double height) {
    if (length < 0.0 || width < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * height * (length + width);
}

int main(void) {
    double length = 10.0;
    double width = 5.0;
    double height = 4.0;
    double lateral_surface_area;

    lateral_surface_area = calculate_lateral_surface_area(length, width, height);

    if (lateral_surface_area < 0.0) {
        fprintf(stderr, "Error: Dimensions must be non-negative.\n");
        return EXIT_FAILURE;
    }

    printf("Lateral Surface Area: %.2f\n", lateral_surface_area);

    return EXIT_SUCCESS;
}