#include <stdio.h>
#include <stdlib.h>

double cuboid_surface_area(double length, double width, double height)
{
    return 2.0 * ((length * width) + (width * height) + (length * height));
}

int main(void)
{
    double length;
    double width;
    double height;

    printf("Enter length: ");
    if (scanf("%lf", &length) != 1) {
        fprintf(stderr, "Invalid input for length\n");
        return EXIT_FAILURE;
    }

    printf("Enter width: ");
    if (scanf("%lf", &width) != 1) {
        fprintf(stderr, "Invalid input for width\n");
        return EXIT_FAILURE;
    }

    printf("Enter height: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Invalid input for height\n");
        return EXIT_FAILURE;
    }

    if (length <= 0.0 || width <= 0.0 || height <= 0.0) {
        fprintf(stderr, "Dimensions must be positive values\n");
        return EXIT_FAILURE;
    }

    printf("Surface area of the cuboid: %.2f\n",
           cuboid_surface_area(length, width, height));

    return EXIT_SUCCESS;
}