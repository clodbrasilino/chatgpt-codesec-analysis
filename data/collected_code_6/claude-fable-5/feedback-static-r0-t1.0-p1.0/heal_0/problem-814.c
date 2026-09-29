#include <stdio.h>
#include <stdlib.h>

double rhombus_area(double d1, double d2)
{
    return (d1 * d2) / 2.0;
}

int main(void)
{
    double d1;
    double d2;

    printf("Enter the first diagonal: ");
    if (scanf("%lf", &d1) != 1) {
        fprintf(stderr, "Invalid input for the first diagonal.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second diagonal: ");
    if (scanf("%lf", &d2) != 1) {
        fprintf(stderr, "Invalid input for the second diagonal.\n");
        return EXIT_FAILURE;
    }

    if (d1 <= 0.0 || d2 <= 0.0) {
        fprintf(stderr, "Diagonals must be positive values.\n");
        return EXIT_FAILURE;
    }

    printf("Area of the rhombus: %.2f\n", rhombus_area(d1, d2));

    return EXIT_SUCCESS;
}