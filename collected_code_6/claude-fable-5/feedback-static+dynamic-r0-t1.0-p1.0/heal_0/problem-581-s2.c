#include <stdio.h>
#include <stdlib.h>

double square_pyramid_surface_area(double base_length, double slant_height)
{
    return (base_length * base_length) + (2.0 * base_length * slant_height);
}

int main(void)
{
    double base_length;
    double slant_height;
    double area;

    printf("Enter the base length of the square pyramid: ");
    if (scanf("%lf", &base_length) != 1) {
        fprintf(stderr, "Error: invalid input for base length.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the slant height of the square pyramid: ");
    if (scanf("%lf", &slant_height) != 1) {
        fprintf(stderr, "Error: invalid input for slant height.\n");
        return EXIT_FAILURE;
    }

    if (base_length <= 0.0 || slant_height <= 0.0) {
        fprintf(stderr, "Error: dimensions must be positive values.\n");
        return EXIT_FAILURE;
    }

    area = square_pyramid_surface_area(base_length, slant_height);

    printf("Surface area of the square pyramid: %.2f\n", area);

    return EXIT_SUCCESS;
}