#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int square_pyramid_surface_area(double base_side, double height,
                                       double *area)
{
    double slant_height;

    if (area == NULL || !isfinite(base_side) || !isfinite(height) ||
        base_side <= 0.0 || height <= 0.0) {
        return 0;
    }

    slant_height = hypot(height, base_side / 2.0);
    *area = base_side * base_side + 2.0 * base_side * slant_height;

    return isfinite(*area);
}

static int parse_positive_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(parsed) || parsed <= 0.0) {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(int argc, char *const argv[])
{
    double base_side;
    double height;
    double area;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base_side> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_positive_double(argv[1], &base_side) ||
        !parse_positive_double(argv[2], &height)) {
        fprintf(stderr, "Error: dimensions must be finite positive numbers.\n");
        return EXIT_FAILURE;
    }

    if (!square_pyramid_surface_area(base_side, height, &area)) {
        fprintf(stderr, "Error: surface area could not be calculated.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}