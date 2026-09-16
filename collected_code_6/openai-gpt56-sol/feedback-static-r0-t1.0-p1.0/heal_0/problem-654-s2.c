#include <stdio.h>
#include <stdlib.h>

static int rectangle_perimeter(double length, double width, double *perimeter)
{
    if (length < 0.0 || width < 0.0 || perimeter == NULL) {
        return -1;
    }

    *perimeter = 2.0 * (length + width);
    return 0;
}

int main(void)
{
    double length;
    double width;
    double perimeter;

    if (printf("Enter length and width: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf", &length, &width) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (rectangle_perimeter(length, width, &perimeter) != 0) {
        fprintf(stderr, "Dimensions must be non-negative.\n");
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}