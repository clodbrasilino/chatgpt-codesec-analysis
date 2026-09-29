#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0;
    }

    *area = (diagonal1 / 2.0) * diagonal2;

    if (!isfinite(*area)) {
        return 0;
    }

    return 1;
}

int main(void)
{
    double diagonal1;
    double diagonal2;
    double area;

    if (printf("Enter the two diagonals of the rhombus: ") < 0) {
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf", &diagonal1, &diagonal2) != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (!rhombus_area(diagonal1, diagonal2, &area)) {
        fprintf(stderr, "Diagonals must be finite positive numbers.\n");
        return EXIT_FAILURE;
    }

    if (printf("Area of the rhombus: %.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}