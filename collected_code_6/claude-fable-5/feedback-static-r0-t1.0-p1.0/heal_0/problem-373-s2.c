#include <stdio.h>
#include <stdlib.h>

double cuboid_volume(double length, double width, double height)
{
    return length * width * height;
}

int main(void)
{
    double length;
    double width;
    double height;
    double volume;

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

    volume = cuboid_volume(length, width, height);
    printf("Volume of the cuboid: %f\n", volume);

    return EXIT_SUCCESS;
}