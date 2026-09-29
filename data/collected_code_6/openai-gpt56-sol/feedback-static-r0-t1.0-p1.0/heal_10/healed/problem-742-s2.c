#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int tetrahedron_surface_area(double edge, double *area)
{
    const double root_three = 1.7320508075688772935;

    if (area == NULL || !isfinite(edge) || edge <= 0.0) {
        return 0;
    }

    if (edge > sqrt(DBL_MAX / root_three)) {
        return 0;
    }

    *area = root_three * edge * edge;
    return isfinite(*area);
}

int main(void)
{
    char input[256];
    char *end;
    double edge;
    double area;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL) {
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            fputs("Input is too long.\n", stderr);
            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read the edge length.\n", stderr);
            return EXIT_FAILURE;
        }
    } else {
        input[strcspn(input, "\n")] = '\0';
    }

    errno = 0;
    edge = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid edge length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0') {
        unsigned char c = (unsigned char)*end;

        if (c != ' ' && c != '\t' && c != '\r' &&
            c != '\v' && c != '\f') {
            fputs("Unexpected characters in input.\n", stderr);
            return EXIT_FAILURE;
        }

        ++end;
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