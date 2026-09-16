#include <stdio.h>
#include <stdlib.h>

double rectangle_perimeter(double length, double width)
{
    return 2.0 * (length + width);
}

int main(void)
{
    double length = 0.0;
    double width = 0.0;

    printf("Enter the length of the rectangle: ");
    if (scanf("%lf", &length) != 1) {
        fprintf(stderr, "Error: invalid input for length.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the width of the rectangle: ");
    if (scanf("%lf", &width) != 1) {
        fprintf(stderr, "Error: invalid input for width.\n");
        return EXIT_FAILURE;
    }

    if (length <= 0.0 || width <= 0.0) {
        fprintf(stderr, "Error: dimensions must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter of the rectangle: %.2f\n", rectangle_perimeter(length, width));

    return EXIT_SUCCESS;
}