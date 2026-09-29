#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_surface_area(double radius, double *area)
{
    const double pi = 3.14159265358979323846;

    if (area == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    *area = pi * radius * radius;

    if (!isfinite(*area)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[256];
    char *end = NULL;
    double radius;
    double area;

    printf("Enter the cylinder radius: ");

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || radius < 0.0) {
        fprintf(stderr, "Radius must be a non-negative number.\n");
        return EXIT_FAILURE;
    }

    if (calculate_surface_area(radius, &area) != 0) {
        fprintf(stderr, "Unable to calculate the surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Top or bottom surface area: %.10g\n", area);

    return EXIT_SUCCESS;
}