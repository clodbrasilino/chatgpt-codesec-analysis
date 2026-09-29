#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_regular_polygon_area(size_t sides, double side_length,
                                          double *area)
{
    double angle;
    double tangent;
    double result;

    if (area == NULL || sides < 3U || !isfinite(side_length) ||
        side_length <= 0.0) {
        return 0;
    }

    angle = acos(-1.0) / (double)sides;
    tangent = tan(angle);

    if (!isfinite(tangent) || tangent <= 0.0) {
        return 0;
    }

    result = ((double)sides * side_length * side_length) / (4.0 * tangent);

    if (!isfinite(result)) {
        return 0;
    }

    *area = result;
    return 1;
}

int main(void)
{
    unsigned long input_sides;
    size_t sides;
    double side_length;
    double area;
    int scan_result;

    printf("Enter the number of sides and the side length: ");
    scan_result = scanf("%lu %lf", &input_sides, &side_length);

    if (scan_result != 2) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (input_sides > (unsigned long)SIZE_MAX) {
        fprintf(stderr, "The number of sides is too large.\n");
        return EXIT_FAILURE;
    }

    sides = (size_t)input_sides;

    errno = 0;
    if (!calculate_regular_polygon_area(sides, side_length, &area) ||
        errno != 0) {
        fprintf(stderr, "Unable to calculate the area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}