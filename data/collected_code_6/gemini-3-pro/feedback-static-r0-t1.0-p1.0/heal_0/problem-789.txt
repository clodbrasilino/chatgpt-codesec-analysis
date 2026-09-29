#include <stdio.h>
#include <stdlib.h>

double calculate_regular_polygon_perimeter(int num_sides, double side_length) {
    if (num_sides < 3 || side_length <= 0.0) {
        return -1.0;
    }
    return (double)num_sides * side_length;
}

int main(void) {
    int sides = 6;
    double length = 5.5;
    double perimeter;

    perimeter = calculate_regular_polygon_perimeter(sides, length);

    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid polygon parameters provided.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}