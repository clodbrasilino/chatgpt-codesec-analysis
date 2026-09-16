#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_perimeter(size_t sides, double side_length, double *perimeter)
{
    if (perimeter == NULL ||
        sides < 3 ||
        !isfinite(side_length) ||
        side_length <= 0.0 ||
        (double)sides > DBL_MAX / side_length) {
        return 0;
    }

    *perimeter = (double)sides * side_length;
    return isfinite(*perimeter);
}

int main(void)
{
    size_t sides;
    double side_length;
    double perimeter;

    if (scanf("%zu %lf", &sides, &side_length) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!calculate_perimeter(sides, side_length, &perimeter)) {
        fprintf(stderr, "Invalid polygon dimensions\n");
        return EXIT_FAILURE;
    }

    printf("%.10g\n", perimeter);
    return EXIT_SUCCESS;
}