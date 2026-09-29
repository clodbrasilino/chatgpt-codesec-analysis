#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_parallelogram_area(double base, double height, double *area)
{
    if (area == NULL || !isfinite(base) || !isfinite(height) ||
        base < 0.0 || height < 0.0) {
        return -1;
    }

    *area = base * height;

    if (!isfinite(*area)) {
        return -1;
    }

    return 0;
}

static int parse_nonnegative_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    *value = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(*value) || *value < 0.0) {
        return -1;
    }

    return 0;
}

int main(int argc, const char *const argv[])
{
    double base;
    double height;
    double area;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <base> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_nonnegative_double(argv[1], &base) != 0 ||
        parse_nonnegative_double(argv[2], &height) != 0) {
        fprintf(stderr, "Base and height must be finite, nonnegative numbers.\n");
        return EXIT_FAILURE;
    }

    if (calculate_parallelogram_area(base, height, &area) != 0) {
        fprintf(stderr, "Unable to calculate the area.\n");
        return EXIT_FAILURE;
    }

    if (printf("Area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}