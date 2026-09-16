#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double pentagon_area(double side)
{
    return (0.25) * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) * side * side;
}

int main(void)
{
    double side = 0.0;
    double area = 0.0;
    int result = 0;

    printf("Enter the side length of the pentagon: ");

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
        fprintf(stderr, "Error: side length is not a finite number.\n");
        return EXIT_FAILURE;
    }

    area = pentagon_area(side);

    if (!isfinite(area)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("The area of the pentagon is: %.6f\n", area);

    return EXIT_SUCCESS;
}