#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_surface_area(double radius, double *area)
{
    const double factor = 4.0 * 3.14159265358979323846;
    const double maximum_radius = sqrt(DBL_MAX / factor);

    if (area == NULL || !isfinite(radius) || radius < 0.0 ||
        radius > maximum_radius) {
        return -1;
    }

    *area = factor * radius * radius;
    return isfinite(*area) ? 0 : -1;
}

static int read_radius(double *radius)
{
    char input[256];
    char *end;
    int ch;

    if (radius == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (!feof(stdin)) {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }
            return ferror(stdin) ? -1 : 1;
        }

        if (ferror(stdin)) {
            return -1;
        }
    }

    errno = 0;
    end = NULL;
    *radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return 1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    return *end == '\0' ? 0 : 1;
}

int main(void)
{
    double radius;
    double area;
    int result = read_radius(&radius);

    if (result != 0) {
        fputs(result < 0 ? "Failed to read the radius.\n"
                         : "Invalid radius.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (sphere_surface_area(radius, &area) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}