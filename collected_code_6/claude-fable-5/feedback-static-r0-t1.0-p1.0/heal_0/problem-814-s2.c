#include <stdio.h>
#include <stdlib.h>

double rhombus_area(double d1, double d2);

double rhombus_area(double d1, double d2)
{
    return (d1 * d2) / 2.0;
}

int main(void)
{
    double d1 = 0.0;
    double d2 = 0.0;
    double area = 0.0;

    printf("Enter the first diagonal: ");
    if (scanf("%lf", &d1) != 1) {
        fprintf(stderr, "Error: invalid input for first diagonal.\n");
        return EXIT_FAILURE;
    }

    printf("Enter the second diagonal: ");
    if (scanf("%lf", &d2) != 1) {
        fprintf(stderr, "Error: invalid input for second diagonal.\n");
        return EXIT_FAILURE;
    }

    if (d1 <= 0.0 || d2 <= 0.0) {
        fprintf(stderr, "Error: diagonals must be positive values.\n");
        return EXIT_FAILURE;
    }

    area = rhombus_area(d1, d2);

    if (printf("Area of the rhombus: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}