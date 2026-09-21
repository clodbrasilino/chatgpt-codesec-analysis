#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    const double pi = acos(-1.0);

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    if (radius > DBL_MAX / (2.0 * pi)) {
        return -1;
    }

    *circumference = 2.0 * pi * radius;

    return isfinite(*circumference) ? 0 : -1;
}

static int read_radius(double *radius)
{
    char input[256];
    char *end;

    if (radius == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    for (size_t i = 0; i < sizeof input; ++i) {
        if (input[i] == '\n') {
            break;
        }

        if (input[i] == '\0') {
            if (!feof(stdin)) {
                char discard[256];

                do {
                    if (fgets(discard, sizeof discard, stdin) == NULL) {
                        break;
                    }
                } while (!feof(stdin) && discard[sizeof discard - 2] != '\n');

                return -1;
            }

            break;
        }
    }

    if (ferror(stdin)) {
        return -1;
    }

    errno = 0;
    *radius = strtod(input, &end);

    if (end == input || errno == ERANGE ||
        !isfinite(*radius) || *radius < 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    return *end == '\0' ? 0 : -1;
}

int main(void)
{
    double radius;
    double circumference;

    if (read_radius(&radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_circumference(radius, &circumference) != 0) {
        fputs("Unable to calculate the circumference.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}