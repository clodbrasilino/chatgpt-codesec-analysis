#include <stdio.h>
#include <stdlib.h>

double square_perimeter(double side)
{
    return 4.0 * side;
}

int main(void)
{
    double side = 0.0;

    printf("Enter the side length of the square: ");

    if (scanf("%lf", &side) != 1) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (side < 0.0) {
        fprintf(stderr, "Error: side length cannot be negative.\n");
        return EXIT_FAILURE;
    }

    printf("Perimeter of the square: %f\n", square_perimeter(side));

    return EXIT_SUCCESS;
}