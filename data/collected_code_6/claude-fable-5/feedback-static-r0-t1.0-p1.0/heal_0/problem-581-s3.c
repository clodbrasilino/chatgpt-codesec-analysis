#include <stdio.h>
#include <stdlib.h>

double square_pyramid_surface_area(double base_side, double slant_height)
{
    return (base_side * base_side) + (2.0 * base_side * slant_height);
}

int main(void)
{
    double base_side;
    double slant_height;
    double area;

    printf("Enter the base side length: ");
    if (scanf("%lf", &base_side) != 1) {
        fprintf(stderr, "Error: invalid input for base side.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the slant height: ");
    if (scanf("%lf", &slant_height) != 1) {
        fprintf(stderr, "Error: invalid input for slant height.\n");
        return EXIT_FAILURE;
    }

    if (base_side <= 0.0 || slant_height <= 0.0) {
        fprintf(stderr, "Error: dimensions must be positive values.\n");
        return EXIT_FAILURE;
    }

    area = square_pyramid_surface_area(base_side, slant_height);

    printf("Surface area of the square pyramid: %.2f\n", area);

    return EXIT_SUCCESS;
}