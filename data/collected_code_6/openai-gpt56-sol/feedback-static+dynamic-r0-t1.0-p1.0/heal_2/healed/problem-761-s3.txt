#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_arc_length(double radius, double angle_degrees,
                                double *arc_length)
{
    const double pi = 3.14159265358979323846;

    if (arc_length == NULL || !isfinite(radius) ||
        !isfinite(angle_degrees) || radius < 0.0) {
        return -1;
    }

    *arc_length = radius * angle_degrees * pi / 180.0;

    return isfinite(*arc_length) ? 0 : -1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    *value = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' || !isfinite(*value)) {
        return -1;
    }

    return 0;
}

int main(int argc, const char *argv[])
{
    double radius;
    double angle_degrees;
    double arc_length;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <angle-degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &radius) != 0 ||
        parse_double(argv[2], &angle_degrees) != 0) {
        fprintf(stderr, "Invalid numeric input.\n");
        return EXIT_FAILURE;
    }

    if (calculate_arc_length(radius, angle_degrees, &arc_length) != 0) {
        fprintf(stderr, "Unable to calculate arc length.\n");
        return EXIT_FAILURE;
    }

    printf("%.10g\n", arc_length);
    return EXIT_SUCCESS;
}