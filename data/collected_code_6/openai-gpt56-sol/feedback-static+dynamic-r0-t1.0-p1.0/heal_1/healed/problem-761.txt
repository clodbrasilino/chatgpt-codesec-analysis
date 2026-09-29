#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_arc_length(double radius, double angle_degrees,
                                double *arc_length)
{
    if (arc_length == NULL || !isfinite(radius) ||
        !isfinite(angle_degrees) || radius < 0.0) {
        return 0;
    }

    const double pi = acos(-1.0);
    const double result = radius * angle_degrees * pi / 180.0;

    if (!isfinite(result)) {
        return 0;
    }

    *arc_length = result;
    return 1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    const double parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(parsed)) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(int argc, char *const argv[])
{
    double radius = 0.0;
    double angle_degrees = 0.0;
    double arc_length = 0.0;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <angle_degrees>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_double(argv[1], &radius) ||
        !parse_double(argv[2], &angle_degrees)) {
        fprintf(stderr, "Invalid numeric input.\n");
        return EXIT_FAILURE;
    }

    if (!calculate_arc_length(radius, angle_degrees, &arc_length)) {
        fprintf(stderr, "Unable to calculate arc length.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", arc_length) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}