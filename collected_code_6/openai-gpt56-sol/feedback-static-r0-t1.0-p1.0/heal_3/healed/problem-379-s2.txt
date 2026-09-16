#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cuboid_surface_area(double length, double width, double height,
                               double *area)
{
    double result;

    if (area == NULL || !isfinite(length) || !isfinite(width) ||
        !isfinite(height) || length < 0.0 || width < 0.0 || height < 0.0) {
        return -1;
    }

    result = 2.0 * (length * width + length * height + width * height);

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

static int parse_dimension(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
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
    double length;
    double width;
    double height;
    double area;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <length> <width> <height>\n",
                argc > 0 && argv != NULL && argv[0] != NULL
                    ? argv[0]
                    : "cuboid");
        return EXIT_FAILURE;
    }

    if (argv == NULL ||
        parse_dimension(argv[1], &length) != 0 ||
        parse_dimension(argv[2], &width) != 0 ||
        parse_dimension(argv[3], &height) != 0) {
        fputs("Dimensions must be finite, non-negative numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cuboid_surface_area(length, width, height, &area) != 0) {
        fputs("Unable to calculate a finite surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}