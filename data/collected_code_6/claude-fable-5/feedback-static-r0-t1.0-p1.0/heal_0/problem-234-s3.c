#include <stdio.h>
#include <stdlib.h>

double cube_volume(double side)
{
    return side * side * side;
}

int main(void)
{
    double side = 0.0;
    int result = 0;

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

    printf("Volume of the cube: %f\n", cube_volume(side));

    return EXIT_SUCCESS;
}