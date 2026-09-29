#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { SIDE_COUNT = 5 };

static int pentagon_perimeter(const double sides[static SIDE_COUNT],
                              double *result)
{
    double perimeter = 0.0;

    if (sides == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0 ||
            sides[i] > DBL_MAX - perimeter) {
            return -1;
        }

        perimeter += sides[i];
    }

    *result = perimeter;
    return 0;
}

static int read_side(double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    char *start;
    char *end;
    double parsed;
    ssize_t length;

    if (value == NULL) {
        return -1;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    start = line;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtod(start, &end);

    if (end == start || errno == ERANGE || !isfinite(parsed) || parsed <= 0.0) {
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

    *value = parsed;
    free(line);
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

    if (pentagon_perimeter(sides, &perimeter) != 0) {
        fputs("Unable to calculate perimeter\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}