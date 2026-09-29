#include <stdio.h>
#include <stdlib.h>

double pentagon_perimeter(double side);

double pentagon_perimeter(double side)
{
    return 5.0 * side;
}

int main(void)
{
    double side = 0.0;
    double perimeter = 0.0;
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

    perimeter = pentagon_perimeter(side);
    printf("The perimeter of the pentagon is: %.2f\n", perimeter);

    return EXIT_SUCCESS;
}