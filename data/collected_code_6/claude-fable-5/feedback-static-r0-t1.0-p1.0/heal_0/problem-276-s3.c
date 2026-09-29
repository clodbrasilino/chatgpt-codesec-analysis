#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cylinder_volume(double radius, double height)
{
    return M_PI * radius * radius * height;
}

int main(void)
{
    double radius;
    double height;

    printf("Enter the radius of the cylinder: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: invalid input for radius.\n");
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: radius cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the height of the cylinder: ");
    if (scanf("%lf", &height) != 1) {
        fprintf(stderr, "Error: invalid input for height.\n");
        return EXIT_FAILURE;
    }

    if (height < 0.0) {
        fprintf(stderr, "Error: height cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Volume of the cylinder: %.4f\n", cylinder_volume(radius, height));

    return EXIT_SUCCESS;
}