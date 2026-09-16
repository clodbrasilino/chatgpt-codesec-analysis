#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double cube_volume(double side);

double cube_volume(double side)
{
    return side * side * side;
}

int main(void)
{
    double side = 0.0;
    double volume = 0.0;

    printf("Enter the side length of the cube: ");

    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (side < 0.0 || !isfinite(side)) {
        fprintf(stderr, "Error: side length must be a non-negative finite number.\n");
        return EXIT_FAILURE;
    }

    volume = cube_volume(side);

    if (!isfinite(volume)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Volume of the cube: %f\n", volume);

    return EXIT_SUCCESS;
}