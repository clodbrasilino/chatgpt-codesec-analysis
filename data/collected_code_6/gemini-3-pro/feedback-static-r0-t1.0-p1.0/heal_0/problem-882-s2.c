#include <stdio.h>
#include <stdlib.h>

double calculate_parallelogram_perimeter(double side_a, double side_b) {
    if (side_a <= 0.0 || side_b <= 0.0) {
        return -1.0;
    }
    return 2.0 * (side_a + side_b);
}

int main(void) {
    double side_a = 5.0;
    double side_b = 7.5;
    double perimeter;

    perimeter = calculate_parallelogram_perimeter(side_a, side_b);

    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Invalid side lengths provided. Lengths must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}