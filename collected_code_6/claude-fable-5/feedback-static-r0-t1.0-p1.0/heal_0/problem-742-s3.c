#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tetrahedron_area(double side)
{
    return sqrt(3.0) * side * side;
}

int main(void)
{
    double side = 0.0;
    double area = 0.0;
    int result = 0;

    printf("Enter the side length of the tetrahedron: ");
    result = scanf("%lf", &side);

    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (side <= 0.0) {
        fprintf(stderr, "Error: side length must be positive.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(side)) {
        fprintf(stderr, "Error: side length must be a finite number.\n");
        return EXIT_FAILURE;
    }

    area = tetrahedron_area(side);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("The surface area of the tetrahedron is: %f\n", area);

    return EXIT_SUCCESS;
}