#include <stdio.h>
#include <stdlib.h>

double triangular_prism_volume(double base, double height, double length)
{
    return 0.5 * base * height * length;
}

int main(void)
{
    double base;
    double height;
    double length;
    double volume;

    printf("Enter the base of the triangle: ");
    if (scanf("%lf", &base) != 1) {
        fprintf(stderr, "Error: invalid input for base.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the triangle: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the length of the prism: ");
    if (scanf("%lf", &length) != 1) {
        fprintf(stderr, "Error: invalid input for length.\n");
        return EXIT_FAILURE;
    }

    if (base <= 0.0 || height <= 0.0 || length <= 0.0) {
        fprintf(stderr, "Error: all dimensions must be positive values.\n");
        return EXIT_FAILURE;
    }

    volume = triangular_prism_volume(base, height, length);

    printf("Volume of the triangular prism: %.2f\n", volume);

    return EXIT_SUCCESS;
}