#include <ctype.h>
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

    if (radius > sqrt(DBL_MAX / pi)) {
        return -1;
    }

    *area = pi * radius * radius;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    double radius;
    double area;

    printf("Enter the cylinder radius: ");
    fflush(stdout);

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        fprintf(stderr, "Failed to read the radius.\n");
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        fprintf(stderr, "Invalid radius.\n");
        free(input);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || radius < 0.0) {
        fprintf(stderr, "Radius must be a non-negative number.\n");
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (calculate_surface_area(radius, &area) != 0) {
        fprintf(stderr, "Unable to calculate the surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Top or bottom surface area: %.10g\n", area);
    return EXIT_SUCCESS;
}