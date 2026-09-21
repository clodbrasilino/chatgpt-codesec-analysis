#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL ||
        !isfinite(radius) ||
        radius < 0.0 ||
        radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = radius * 2.0;
    return 0;
}

static int read_radius(double *radius)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;

    if (radius == NULL) {
        return -1;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    errno = 0;
    *radius = strtod(line, &end);

    if (end == line || errno == ERANGE) {
        free(line);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    free(line);
    return 0;
}

int main(void)
{
    double radius;
    double diameter;

    fputs("Enter the radius: ", stdout);
    fflush(stdout);

    if (read_radius(&radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_diameter(radius, &diameter) != 0) {
        fputs("Radius must be a finite, nonnegative number in range.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Diameter: %.10g\n", diameter);
    return EXIT_SUCCESS;
}