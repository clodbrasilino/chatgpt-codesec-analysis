#include <stdio.h>
#include <stdlib.h>

double polygon_perimeter(int num_sides, double side_length)
{
    return (double)num_sides * side_length;
}

int main(void)
{
    int num_sides = 0;
    double side_length = 0.0;
    double perimeter = 0.0;

    printf("Enter the number of sides: ");
    if (scanf("%d", &num_sides) != 1) {
        fprintf(stderr, "Error: invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }

    if (num_sides < 3) {
        fprintf(stderr, "Error: a polygon must have at least 3 sides.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the side length: ");
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Error: invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    if (side_length <= 0.0) {
        fprintf(stderr, "Error: side length must be positive.\n");
        return EXIT_FAILURE;
    }

    perimeter = polygon_perimeter(num_sides, side_length);

    printf("The perimeter of the regular polygon is: %.6f\n", perimeter);

    return EXIT_SUCCESS;
}