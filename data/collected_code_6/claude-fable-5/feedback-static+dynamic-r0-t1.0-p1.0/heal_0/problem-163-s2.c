#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double polygon_area(int num_sides, double side_length)
{
    double numerator;
    double denominator;

    numerator = (double)num_sides * side_length * side_length;
    denominator = 4.0 * tan(M_PI / (double)num_sides);

    return numerator / denominator;
}

int main(void)
{
    int num_sides;
    double side_length;
    double area;
    int result;

    printf("Enter the number of sides: ");
    result = scanf("%d", &num_sides);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for number of sides.\n");
        return EXIT_FAILURE;
    }

    if (num_sides < 3) {
        fprintf(stderr, "Error: a polygon must have at least 3 sides.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the side length: ");
    result = scanf("%lf", &side_length);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    if (side_length <= 0.0 || !isfinite(side_length)) {
        fprintf(stderr, "Error: side length must be a positive finite number.\n");
        return EXIT_FAILURE;
    }

    area = polygon_area(num_sides, side_length);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("The area of the regular polygon is: %.6f\n", area);

    return EXIT_SUCCESS;
}