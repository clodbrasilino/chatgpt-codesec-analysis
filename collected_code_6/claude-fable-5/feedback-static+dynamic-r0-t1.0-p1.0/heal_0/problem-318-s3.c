#include <stdio.h>
#include <stdlib.h>

static double max_cuboid_volume(double sum_of_sides)
{
    double side;

    if (sum_of_sides <= 0.0) {
        return -1.0;
    }

    side = sum_of_sides / 3.0;
    return side * side * side;
}

int main(void)
{
    double sum_of_sides;
    double volume;
    int result;

    printf("Enter the sum of the sides of the cuboid: ");

    result = scanf("%lf", &sum_of_sides);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    volume = max_cuboid_volume(sum_of_sides);
    if (volume < 0.0) {
        fprintf(stderr, "Error: sum of sides must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Maximum volume: %f\n", volume);

    return EXIT_SUCCESS;
}