#include <stdio.h>
#include <stdlib.h>

double rectangle_perimeter(double length, double width)
{
    return 2.0 * (length + width);
}

int main(void)
{
    double length;
    double width;
    double perimeter;

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
        fprintf(stderr, "Error: dimensions must be positive values.\n");
        return EXIT_FAILURE;
    }

    perimeter = rectangle_perimeter(length, width);

    printf("The perimeter of the rectangle is: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}