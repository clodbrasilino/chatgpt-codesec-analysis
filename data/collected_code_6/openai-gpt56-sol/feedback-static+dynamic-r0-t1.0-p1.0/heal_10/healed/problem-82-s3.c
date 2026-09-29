#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static double sphere_volume(double radius)
{
    const double pi = acos(-1.0);
    return (4.0 / 3.0) * pi * radius * radius * radius;
}

static int read_radius(double *radius)
{
    char input[256];
    char *start;
    char *end;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        errno = EOVERFLOW;
        return 0;
    }

    start = input;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    *radius = strtod(start, &end);

    if (end == start || errno == ERANGE || !isfinite(*radius) || *radius < 0.0) {
        errno = EINVAL;
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        errno = EINVAL;
        return 0;
    }

    return 1;
}

int main(void)
{
    double radius;
    double volume;

    errno = 0;
    if (!read_radius(&radius)) {
        if (errno == EOVERFLOW) {
            fputs("Input is too large.\n", stderr);
        } else {
            fputs("Invalid radius.\n", stderr);
        }
        return EXIT_FAILURE;
    }

    volume = sphere_volume(radius);

    if (!isfinite(volume)) {
        fputs("Volume is outside the representable range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}