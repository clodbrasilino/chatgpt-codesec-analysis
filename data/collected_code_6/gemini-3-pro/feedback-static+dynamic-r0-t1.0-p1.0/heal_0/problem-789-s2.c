#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double calculate_polygon_perimeter(int sides, double side_length) {
    if (sides < 3) {
        return -1.0;
    }
    if (side_length <= 0) {
        return -1.0;
    }
    return (double)sides * side_length;
}

int main(void) {
    int sides;
    double side_length;
    double perimeter;

    if (scanf("%d", &sides) != 1) {
        fprintf(stderr, "Invalid input for sides.\n");
        return EXIT_FAILURE;
    }

    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Invalid input for side length.\n");
        return EXIT_FAILURE;
    }

    perimeter = calculate_polygon_perimeter(sides, side_length);

    if (perimeter < 0.0) {
        fprintf(stderr, "Invalid polygon parameters.\n");
        return EXIT_FAILURE;
    }

    printf("%f\n", perimeter);

    return EXIT_SUCCESS;
}