#include <stdio.h>
#include <stdlib.h>

double calculate_rhombus_perimeter(double side);

double calculate_rhombus_perimeter(double side) {
    if (side <= 0.0) {
        return -1.0;
    }
    return 4.0 * side;
}

int main(void) {
    double side = 5.0;
    double perimeter = calculate_rhombus_perimeter(side);

    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid side length\n");
        return EXIT_FAILURE;
    }

    printf("%.2f\n", perimeter);

    return EXIT_SUCCESS;
}