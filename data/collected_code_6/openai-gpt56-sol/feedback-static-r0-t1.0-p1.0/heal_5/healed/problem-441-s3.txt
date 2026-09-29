#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define INPUT_SIZE 256

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
    char input[INPUT_SIZE];
    char *end;
    double side;
    double area;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the cube's side length.\n", stderr);
        return EXIT_FAILURE;
    }

    end = input;
    while (*end != '\0' && *end != '\n') {
        ++end;
    }

    if (*end == '\n') {
        *end = '\0';
    } else {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ferror(stdin)) {
                fputs("Failed to read the cube's side length.\n", stderr);
            } else {
                fputs("Input is too long.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (ferror(stdin)) {
            fputs("Failed to read the cube's side length.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(side)) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid trailing input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_surface_area(side, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}