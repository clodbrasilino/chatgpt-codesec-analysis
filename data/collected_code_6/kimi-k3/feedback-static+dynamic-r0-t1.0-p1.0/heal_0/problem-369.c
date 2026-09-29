#include <stdio.h>

double calculateLateralSurfaceArea(double length, double width, double height) {
    return 2 * height * (length + width);
}

int main(void) {
    double length = 0.0;
    double width = 0.0;
    double height = 0.0;
    double lateralSurfaceArea = 0.0;

    printf("Enter length of cuboid: ");
    if (scanf("%lf", &length) != 1) {
        fprintf(stderr, "Error: Invalid input for length\n");
        return 1;
    }

    printf("Enter width of cuboid: ");
    if (scanf("%lf", &width) != 1) {
        fprintf(stderr, "Error: Invalid input for width\n");
        return 1;
    }

    printf("Enter height of cuboid: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: Invalid input for height\n");
        return 1;
    }

    if (length <= 0.0 || width <= 0.0 || height <= 0.0) {
        fprintf(stderr, "Error: All dimensions must be positive values\n");
        return 1;
    }

    lateralSurfaceArea = calculateLateralSurfaceArea(length, width, height);

    printf("Lateral Surface Area of cuboid: %.2f\n", lateralSurfaceArea);

    return 0;
}