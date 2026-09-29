#include <stdio.h>
#include <math.h>
#include <stdbool.h>

bool lateral_surface_area_cone(double radius, double slant_height, double *result) {
    if (radius < 0 || slant_height < 0) {
        return false;
    }
    if (result == NULL) {
        return false;
    }
    *result = M_PI * radius * slant_height;
    return true;
}

int main(void) {
    double radius = 0.0;
    double slant_height = 0.0;
    double area = 0.0;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }

    printf("Enter slant height: ");
    if (scanf("%lf", &slant_height) != 1) {
        fprintf(stderr, "Invalid input for slant height\n");
        return 1;
    }

    if (!lateral_surface_area_cone(radius, slant_height, &area)) {
        fprintf(stderr, "Invalid cone dimensions\n");
        return 1;
    }

    printf("Lateral surface area: %.2f\n", area);
    return 0;
}