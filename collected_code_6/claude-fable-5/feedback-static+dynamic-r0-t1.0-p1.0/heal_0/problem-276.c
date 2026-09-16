#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cylinder_volume(double radius, double height);

double cylinder_volume(double radius, double height)
{
    return M_PI * radius * radius * height;
}

int main(void)
{
    double radius = 0.0;
    double height = 0.0;
    double volume = 0.0;

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

    volume = cylinder_volume(radius, height);

    if (isinf(volume) || isnan(volume)) {
        fprintf(stderr, "Error: computation overflow or invalid result.\n");
        return EXIT_FAILURE;
    }

    printf("The volume of the cylinder is: %.6f\n", volume);

    return EXIT_SUCCESS;
}