#include <stdio.h>
#include <stdlib.h>

double cube_surface_area(double side)
{
    return 6.0 * side * side;
}

int main(void)
{
    double side = 0.0;
    int result;

    printf("Enter the side length of the cube: ");
    result = scanf("%lf", &side);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (side < 0.0) {
        fprintf(stderr, "Error: side length cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area of the cube: %.2f\n", cube_surface_area(side));

    return EXIT_SUCCESS;
}