#include <stdio.h>
#include <stdlib.h>

double cylinder_perimeter(double radius, double height)
{
    return 2.0 * ((2.0 * radius) + height);
}

int main(void)
{
    double radius = 0.0;
    double height = 0.0;

    printf("Enter the radius of the cylinder: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    if (radius <= 0.0) {
        fprintf(stderr, "Error: radius must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cylinder: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    if (height <= 0.0) {
        fprintf(stderr, "Error: height must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter of the cylinder: %.2f\n", cylinder_perimeter(radius, height));

    return EXIT_SUCCESS;
}