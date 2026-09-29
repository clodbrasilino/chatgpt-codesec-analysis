#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_surface_area(double edge, double *area)
{
    const double factor = 1.7320508075688772935;

    if (area == NULL || !isfinite(edge) || edge <= 0.0 ||
        edge > sqrt(DBL_MAX / factor)) {
        return 0;
    }

    *area = factor * edge * edge;
    return isfinite(*area);
}

int main(void)
{
    char input[256];
    char *end;
    double edge;
    double area;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (!feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        if (ferror(stdin)) {
            fputs("Failed to read the edge length.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    edge = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Unexpected characters in input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!tetrahedron_surface_area(edge, &area)) {
        fputs("Edge length must be a finite positive number within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}