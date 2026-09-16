#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_volume(double radius, double *volume)
{
    const double pi = 3.14159265358979323846;

    if (volume == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    errno = 0;
    *volume = (4.0 / 3.0) * pi * radius * radius * radius;

    if (errno == ERANGE || !isfinite(*volume)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[256];
    char *end = NULL;
    double radius;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || sphere_volume(radius, &volume) != 0) {
        fputs("Invalid radius or volume out of range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}