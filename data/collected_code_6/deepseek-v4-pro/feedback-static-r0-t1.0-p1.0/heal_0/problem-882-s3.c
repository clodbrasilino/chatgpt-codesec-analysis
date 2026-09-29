#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_perimeter(double base, double side);

int main(void) {
    double base = 0.0;
    double side = 0.0;
    double perimeter = 0.0;

    printf("Enter the length of the base: ");
    if (scanf("%lf", &base) != 1) {
        fprintf(stderr, "Invalid input for base.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the length of the side: ");
    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Invalid input for side.\n");
        return EXIT_FAILURE;
    }

    if (base <= 0.0 || side <= 0.0) {
        fprintf(stderr, "Lengths must be positive.\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_perimeter(base, side);
    printf("Perimeter: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}

double calculate_perimeter(double base, double side) {
    return 2.0 * (base + side);
}