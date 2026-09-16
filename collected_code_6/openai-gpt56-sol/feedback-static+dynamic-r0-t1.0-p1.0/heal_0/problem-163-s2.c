#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int regular_polygon_area(size_t sides, double side_length, double *area)
{
    double angle;
    double tangent;
    double result;

    if (area == NULL || sides < 3U || !isfinite(side_length) || side_length <= 0.0) {
        return -1;
    }

    angle = acos(-1.0) / (double)sides;
    tangent = tan(angle);

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

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long parsed_sides;
    double side_length;
    double area;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_sides> <side_length>\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed_sides = strtoul(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\0' ||
        parsed_sides < 3UL || parsed_sides > (unsigned long)SIZE_MAX) {
        fprintf(stderr, "Invalid number of sides.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    side_length = strtod(argv[2], &end);
    if (errno != 0 || end == argv[2] || *end != '\0' ||
        !isfinite(side_length) || side_length <= 0.0) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    if (regular_polygon_area((size_t)parsed_sides, side_length, &area) != 0) {
        fprintf(stderr, "Unable to calculate the area.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}