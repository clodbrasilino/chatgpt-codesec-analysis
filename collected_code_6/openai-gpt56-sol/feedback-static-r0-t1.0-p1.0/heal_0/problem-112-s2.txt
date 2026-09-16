#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    *result = 2.0 * (2.0 * acos(-1.0) * radius + height);

    return isfinite(*result) ? 0 : -1;
}

int main(void)
{
    char input[256];
    char *end = NULL;
    double radius;
    double height;
    double perimeter;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);
    if (end == input || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    errno = 0;
    height = strtod(end, &end);
    if (errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' ||
        cylinder_perimeter(radius, height, &perimeter) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}