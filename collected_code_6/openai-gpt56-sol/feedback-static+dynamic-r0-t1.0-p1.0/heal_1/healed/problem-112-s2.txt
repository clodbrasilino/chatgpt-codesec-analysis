#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    double pi;
    double value;

    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    pi = acos(-1.0);
    value = 2.0 * (2.0 * pi * radius + height);

    if (!isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

int main(void)
{
    char input[256];
    char extra[2];
    char *cursor;
    char *end;
    double radius;
    double height;
    double perimeter;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && scanf("%1s", extra) == 1) {
        return EXIT_FAILURE;
    }

    cursor = input;

    errno = 0;
    radius = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    cursor = end;
    errno = 0;
    height = strtod(cursor, &end);
    if (end == cursor || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    cursor = end;
    while (*cursor == ' ' || *cursor == '\t' || *cursor == '\n' ||
           *cursor == '\r' || *cursor == '\f' || *cursor == '\v') {
        ++cursor;
    }

    if (*cursor != '\0') {
        return EXIT_FAILURE;
    }

    if (cylinder_perimeter(radius, height, &perimeter) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}