#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cuboid_volume(double length, double width, double height, double *volume)
{
    if (volume == NULL ||
        !isfinite(length) || !isfinite(width) || !isfinite(height) ||
        length < 0.0 || width < 0.0 || height < 0.0) {
        return -1;
    }

    *volume = length * width * height;

    return isfinite(*volume) ? 0 : -1;
}

static int parse_dimension(const char *text, double *value)
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

int main(int argc, char *argv[])
{
    double length;
    double width;
    double height;
    double volume;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <length> <width> <height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_dimension(argv[1], &length) != 0 ||
        parse_dimension(argv[2], &width) != 0 ||
        parse_dimension(argv[3], &height) != 0) {
        fputs("Error: dimensions must be finite, non-negative numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cuboid_volume(length, width, height, &volume) != 0) {
        fputs("Error: unable to calculate a finite volume.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Volume: %.17g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}