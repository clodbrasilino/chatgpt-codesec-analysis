#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_area(double side, double *area)
{
    const double factor =
        0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0)));

    if (area == NULL || !isfinite(side) || side <= 0.0) {
        return -1;
    }

    if (side > sqrt(DBL_MAX / factor)) {
        return -1;
    }

    *area = factor * side * side;

    return isfinite(*area) && *area > 0.0 ? 0 : -1;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double side;
    double area;

    fputs("Enter the side length of a regular pentagon: ", stdout);
    fflush(stdout);

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Unexpected input after the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (pentagon_area(side, &area) != 0) {
        fputs("The side length must produce a finite positive area.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Area: %.6f\n", area);
    return EXIT_SUCCESS;
}