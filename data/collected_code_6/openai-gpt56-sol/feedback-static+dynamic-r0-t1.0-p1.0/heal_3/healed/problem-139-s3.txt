#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = 2.0 * pi * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *circumference = result;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double circumference;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end != '\n') {
        if (!feof(stdin)) {
            return EXIT_FAILURE;
        }
    } else {
        *end = '\0';
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (calculate_circumference(radius, &circumference) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}