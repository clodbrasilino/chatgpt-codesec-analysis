#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double regular_polygon_area(int num_sides, double side_length) {
    if (num_sides < 3 || side_length <= 0.0) {
        return -1.0;
    }
    return (num_sides * side_length * side_length) / (4.0 * tan(M_PI / num_sides));
}

int main(void) {
    int num_sides;
    double side_length;
    double area;

    printf("Enter number of sides: ");
    if (scanf("%d", &num_sides) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    printf("Enter side length: ");
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    area = regular_polygon_area(num_sides, side_length);
    if (area < 0.0) {
        fprintf(stderr, "Invalid polygon parameters\n");
        return EXIT_FAILURE;
    }

    printf("Area: %f\n", area);
    return EXIT_SUCCESS;
}