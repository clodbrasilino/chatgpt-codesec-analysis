#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_perimeter(const double sides[static 5], double *result)
{
    double perimeter = 0.0;

    if (sides == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < 5; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0) {
            return -1;
        }

        perimeter += sides[i];

        if (!isfinite(perimeter)) {
            return -1;
        }
    }

    *result = perimeter;
    return 0;
}

int main(void)
{
    double sides[5];
    double perimeter;

    for (size_t i = 0; i < 5; ++i) {
        char input[128];
        char *end;
        double value;

        if (fgets(input, sizeof input, stdin) == NULL) {
            fputs("Input error\n", stderr);
            return EXIT_FAILURE;
        }

        errno = 0;
        end = NULL;
        value = strtod(input, &end);

        if (end == input || errno == ERANGE || !isfinite(value) || value <= 0.0) {
            fputs("Invalid side length\n", stderr);
            return EXIT_FAILURE;
        }

        while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') {
            ++end;
        }

        if (*end != '\0') {
            fputs("Invalid side length\n", stderr);
            return EXIT_FAILURE;
        }

        sides[i] = value;
    }

    if (pentagon_perimeter(sides, &perimeter) != 0) {
        fputs("Unable to calculate perimeter\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}