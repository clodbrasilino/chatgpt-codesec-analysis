#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

enum { SIDE_COUNT = 5, INPUT_SIZE = 128 };

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_side(double *side)
{
    char input[INPUT_SIZE];
    char *end;
    double value;
    size_t length;

    if (side == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    for (length = 0; length < sizeof input && input[length] != '\0'; ++length) {
    }

    if (length == sizeof input) {
        return -1;
    }

    if (length > 0 && input[length - 1] == '\n') {
        input[--length] = '\0';

        if (length > 0 && input[length - 1] == '\r') {
            input[--length] = '\0';
        }
    } else if (!feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    errno = 0;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(value) || value <= 0.0) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\v' ||
           *end == '\f' || *end == '\r' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *side = value;
    return 0;
}

static int pentagon_perimeter(const double sides[SIDE_COUNT], double *result)
{
    double perimeter = 0.0;
    size_t i;

    if (sides == NULL || result == NULL) {
        return -1;
    }

    for (i = 0; i < SIDE_COUNT; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0) {
            return -1;
        }

        if (sides[i] > DBL_MAX - perimeter) {
            return -1;
        }

        perimeter += sides[i];
    }

    *result = perimeter;
    return 0;
}

int main(void)
{
    double sides[SIDE_COUNT];
    double perimeter;
    size_t i;

    for (i = 0; i < SIDE_COUNT; ++i) {
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