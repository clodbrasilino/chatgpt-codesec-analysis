#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_perimeter(size_t side_count, double side_length, double *perimeter)
{
    if (perimeter == NULL || side_count < 3U || !isfinite(side_length) ||
        side_length <= 0.0) {
        return -1;
    }

    if (side_length > DBL_MAX / (double)side_count) {
        return -1;
    }

    *perimeter = (double)side_count * side_length;
    return 0;
}

int main(void)
{
    size_t side_count;
    double side_length;
    double perimeter;
    int result;

    result = scanf("%zu %lf", &side_count, &side_length);
    if (result != 2) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_perimeter(side_count, side_length, &perimeter) != 0) {
        fputs("Invalid polygon dimensions\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}