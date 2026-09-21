#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cylinder_surface_area(double radius, double height, double *area)
{
    const double pi = acos(-1.0);

    if (area == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    if (radius != 0.0 &&
        radius + height > DBL_MAX / (2.0 * pi * radius)) {
        return -1;
    }

    *area = 2.0 * pi * radius * (radius + height);
    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    char input[256];
    char *end;
    char *height_start;
    double radius;
    double height;
    double area;

    fputs("Enter radius and height: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);
    if (end == input || errno == ERANGE || !isfinite(radius)) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    height_start = end;
    errno = 0;
    height = strtod(height_start, &end);
    if (end == height_start || errno == ERANGE || !isfinite(height)) {
        fputs("Invalid height.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cylinder_surface_area(radius, height, &area) != 0) {
        fputs("Unable to calculate surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Surface area: %.6f\n", area);
    return EXIT_SUCCESS;
}