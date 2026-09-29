#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { SIDE_COUNT = 5, INPUT_SIZE = 128 };

static int read_side(double *side)
{
    char input[INPUT_SIZE];
    char *end;
    double value;

    if (side == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    errno = 0;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(value) || value <= 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *side = value;
    return 0;
}

static int pentagon_perimeter(const double *sides, size_t count, double *result)
{
    double perimeter = 0.0;

    if (sides == NULL || result == NULL || count != SIDE_COUNT) {
        return -1;
    }

    for (size_t i = 0; i < count; ++i) {
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
    double sides[SIDE_COUNT];
    double perimeter;

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (read_side(&sides[i]) != 0) {
            fputs("Invalid side length\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (pentagon_perimeter(sides, SIDE_COUNT, &perimeter) != 0) {
        fputs("Unable to calculate perimeter\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}