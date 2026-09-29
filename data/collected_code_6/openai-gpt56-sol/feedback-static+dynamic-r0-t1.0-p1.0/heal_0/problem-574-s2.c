#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_surface_area(double radius, double height, double *area)
{
    const double pi = acos(-1.0);

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    *area = 2.0 * pi * radius * (radius + height);

    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double height;
    double area;

    printf("Enter radius and height: ");
    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);
    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    char *height_start = end;
    errno = 0;
    height = strtod(height_start, &end);
    if (end == height_start || errno == ERANGE) {
        fprintf(stderr, "Invalid height.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Unexpected input.\n");
        return EXIT_FAILURE;
    }

    if (cylinder_surface_area(radius, height, &area) != 0) {
        fprintf(stderr, "Unable to calculate surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Surface area: %.6f\n", area);

    return EXIT_SUCCESS;
}