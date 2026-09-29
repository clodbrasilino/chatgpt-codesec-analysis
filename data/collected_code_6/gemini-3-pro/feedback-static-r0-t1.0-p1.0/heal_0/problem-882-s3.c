#include <stdio.h>
#include <stdlib.h>

double calculate_parallelogram_perimeter(double base, double side) {
    if (base <= 0.0 || side <= 0.0) {
        return -1.0;
    }
    return 2.0 * (base + side);
}

int main(void) {
    double base = 5.0;
    double side = 7.0;
    double perimeter;

    perimeter = calculate_parallelogram_perimeter(base, side);

    if (perimeter < 0.0) {
        fprintf(stderr, "Error: Invalid dimensions.\n");
        return EXIT_FAILURE;
    }

    fprintf(stdout, "Perimeter: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}