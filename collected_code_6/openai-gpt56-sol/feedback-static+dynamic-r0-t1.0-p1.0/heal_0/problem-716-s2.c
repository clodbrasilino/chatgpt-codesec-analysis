#include <stdio.h>
#include <stdlib.h>

static int rhombus_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL || side <= 0.0) {
        return 0;
    }

    *perimeter = 4.0 * side;
    return 1;
}

int main(void)
{
    double side;
    double perimeter;

    printf("Enter the side length of the rhombus: ");

    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!rhombus_perimeter(side, &perimeter)) {
        fprintf(stderr, "Side length must be positive.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter: %.2f\n", perimeter);
    return EXIT_SUCCESS;
}