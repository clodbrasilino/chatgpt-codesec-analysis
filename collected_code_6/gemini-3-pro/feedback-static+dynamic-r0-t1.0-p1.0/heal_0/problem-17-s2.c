#include <stdio.h>
#include <stdlib.h>

double calculate_perimeter(double side) {
    if (side < 0.0) {
        return -1.0;
    }
    return 4.0 * side;
}

int main(void) {
    double side;
    double perimeter;

    if (scanf("%lf", &side) != 1) {
        return EXIT_FAILURE;
    }

    perimeter = calculate_perimeter(side);

    if (perimeter < 0.0) {
        return EXIT_FAILURE;
    }

    printf("%f\n", perimeter);

    return EXIT_SUCCESS;
}