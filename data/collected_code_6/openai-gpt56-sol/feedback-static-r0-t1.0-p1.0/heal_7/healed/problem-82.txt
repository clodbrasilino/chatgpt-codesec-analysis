#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_volume(double radius, double *volume)
{
    static const double pi = 3.14159265358979323846;
    double result;

    if (volume == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = (4.0 / 3.0) * pi * radius * radius * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
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

    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return -1;
    }

    errno = 0;
    *radius = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(*radius)) {
        free(line);
        return -1;
    }

    while (isspace((unsigned char)*end)) {
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
    double volume;

    if (read_radius(&radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sphere_volume(radius, &volume) != 0) {
        fputs("Invalid radius or volume out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}