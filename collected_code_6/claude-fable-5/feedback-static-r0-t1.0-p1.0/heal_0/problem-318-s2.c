#include <stdio.h>
#include <stdlib.h>

double max_cuboid_volume(double side_sum);

double max_cuboid_volume(double side_sum)
{
    double side;

    if (side_sum <= 0.0) {
        return 0.0;
    }

    side = side_sum / 3.0;
    return side * side * side;
}

int main(void)
{
    double sum_of_sides;
    double volume;
    int result;

    printf("Enter the sum of the three sides of the cuboid: ");

    result = scanf("%lf", &sum_of_sides);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (sum_of_sides <= 0.0) {
        fprintf(stderr, "Error: sum of sides must be positive.\n");
        return EXIT_FAILURE;
    }

    volume = max_cuboid_volume(sum_of_sides);
    printf("Maximum volume: %.6f\n", volume);

    return EXIT_SUCCESS;
}