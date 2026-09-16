#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cone_surface_area(double radius, double slant_height, double *area)
{
    const double pi = 3.14159265358979323846;

    if (area == NULL || !isfinite(radius) || !isfinite(slant_height) ||
        radius < 0.0 || slant_height < 0.0) {
        return -1;
    }

    *area = pi * radius * (radius + slant_height);

    return isfinite(*area) ? 0 : -1;
}

static int parse_nonnegative_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return -1;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(parsed) || parsed < 0.0) {
        return -1;
    }

    *value = parsed;
    return 0;
}

int main(int argc, const char *const argv[])
{
    double radius;
    double slant_height;
    double area;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <radius> <slant_height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_nonnegative_double(argv[1], &radius) != 0 ||
        parse_nonnegative_double(argv[2], &slant_height) != 0) {
        fprintf(stderr,
                "Radius and slant height must be finite, nonnegative numbers.\n");
        return EXIT_FAILURE;
    }

    if (cone_surface_area(radius, slant_height, &area) != 0) {
        fprintf(stderr, "Unable to calculate the cone's surface area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Surface area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}