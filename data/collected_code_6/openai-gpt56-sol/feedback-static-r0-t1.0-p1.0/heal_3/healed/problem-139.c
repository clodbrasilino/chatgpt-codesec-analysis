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

    if (!isfinite(*circumference)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double circumference;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = input;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius) || radius < 0.0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0') {
        if (*end != ' ' && *end != '\t' && *end != '\n' &&
            *end != '\r' && *end != '\f' && *end != '\v') {
            fputs("Invalid radius.\n", stderr);
            return EXIT_FAILURE;
        }
        ++end;
    }

    if (ferror(stdin)) {
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