#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_regular_polygon_area(size_t sides, double side_length,
                                          double *area)
{
    double pi;
    double tangent;
    double result;

    if (area == NULL || sides < 3U || !isfinite(side_length) ||
        side_length <= 0.0) {
        return -1;
    }

    pi = acos(-1.0);
    tangent = tan(pi / (double)sides);

    if (!isfinite(tangent) || tangent <= 0.0) {
        return -1;
    }

    result = ((double)sides * side_length * side_length) / (4.0 * tangent);

    if (!isfinite(result) || result <= 0.0) {
        return -1;
    }

    *area = result;
    return 0;
}

int main(void)
{
    unsigned long long input_sides;
    size_t sides;
    double side_length;
    double area;
    int scan_result;

    printf("Enter the number of sides and the side length: ");
    fflush(stdout);

    errno = 0;
    scan_result = scanf("%llu %lf", &input_sides, &side_length);

    if (scan_result != 2 || errno == ERANGE ||
        input_sides > (unsigned long long)SIZE_MAX) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    sides = (size_t)input_sides;

    if (calculate_regular_polygon_area(sides, side_length, &area) != 0) {
        fprintf(stderr, "Unable to calculate the area.\n");
        return EXIT_FAILURE;
    }

    printf("Area: %.10g\n", area);
    return EXIT_SUCCESS;
}