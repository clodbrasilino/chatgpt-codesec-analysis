#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double rhombus_perimeter(double side)
{
    return 4.0 * side;
}

int main(void)
{
    double side = 0.0;
    double perimeter = 0.0;
    int result = 0;

    printf("Enter the side length of the rhombus: ");

    result = scanf("%lf", &side);
    if (result != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!isfinite(side) || side <= 0.0) {
        fprintf(stderr, "Error: side length must be a positive finite number.\n");
        return EXIT_FAILURE;
    }

    perimeter = rhombus_perimeter(side);

    if (!isfinite(perimeter)) {
        fprintf(stderr, "Error: computation overflow.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter of the rhombus: %.6f\n", perimeter);

    return EXIT_SUCCESS;
}