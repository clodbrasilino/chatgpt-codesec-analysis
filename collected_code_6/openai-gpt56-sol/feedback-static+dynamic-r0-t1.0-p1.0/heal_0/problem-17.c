#include <stdio.h>
#include <stdlib.h>

static int square_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL || side < 0.0) {
        return 0;
    }

    *perimeter = 4.0 * side;
    return 1;
}

int main(void)
{
    double side = 0.0;
    double perimeter = 0.0;

    if (scanf("%lf", &side) != 1) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!square_perimeter(side, &perimeter)) {
        fputs("Side length must be nonnegative\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}