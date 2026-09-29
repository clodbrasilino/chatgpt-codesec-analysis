#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int sphere_surface_area(double radius, double *area)
{
    const double factor = 4.0 * 3.14159265358979323846;
    const double max_radius = sqrt(DBL_MAX / factor);

    if (area == NULL || !isfinite(radius) || radius < 0.0 ||
        radius > max_radius) {
        return -1;
    }

    *area = factor * radius * radius;
    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    char input[4097];
    char *end;
    double radius;
    double area;
    int ch;
    size_t length = 0;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        ch = getchar();

        if (ch != '\n' && ch != EOF) {
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);

            if (ferror(stdin)) {
                fputs("Failed to read the radius.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read the radius.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v' || *end == '\n') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sphere_surface_area(radius, &area) != 0) {
        fputs("Radius must be a finite, nonnegative value within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}