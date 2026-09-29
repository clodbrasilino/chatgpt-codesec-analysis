#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_surface_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    if (side > sqrt(DBL_MAX / 6.0)) {
        return -1;
    }

    *area = 6.0 * side * side;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double side;
    double area;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid trailing input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_surface_area(side, &area) != 0) {
        fputs("Side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}