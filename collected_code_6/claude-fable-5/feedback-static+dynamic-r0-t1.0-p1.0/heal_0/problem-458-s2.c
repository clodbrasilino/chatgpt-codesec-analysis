#include <stdio.h>
#include <stdlib.h>

double rectangle_area(double length, double width)
{
    return length * width;
}

int main(void)
{
    double length;
    double width;

    printf("Enter length: ");
    if (scanf("%lf", &length) != 1) {
        fprintf(stderr, "Error: invalid input for length\n");
        return EXIT_FAILURE;
    }

    printf("Enter width: ");
    if (scanf("%lf", &width) != 1) {
        fprintf(stderr, "Error: invalid input for width\n");
        return EXIT_FAILURE;
    }

    if (length < 0.0 || width < 0.0) {
        fprintf(stderr, "Error: dimensions must be non-negative\n");
        return EXIT_FAILURE;
    }

    printf("Area: %f\n", rectangle_area(length, width));

    return EXIT_SUCCESS;
}