#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side <= 0.0) {
        return -1;
    }

    *area = 0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) * side * side;

    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    char input[256];
    char *end = NULL;
    double side;
    double area;

    printf("Enter the side length of a regular pentagon: ");

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fprintf(stderr, "Unexpected input after the side length.\n");
        return EXIT_FAILURE;
    }

    if (pentagon_area(side, &area) != 0) {
        fprintf(stderr, "The side length must be a positive finite number.\n");
        return EXIT_FAILURE;
    }

    printf("Area: %.6f\n", area);

    return EXIT_SUCCESS;
}