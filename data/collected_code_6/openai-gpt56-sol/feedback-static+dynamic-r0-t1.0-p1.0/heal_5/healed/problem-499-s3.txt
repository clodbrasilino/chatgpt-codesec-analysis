#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL || !isfinite(radius) ||
        radius < 0.0 || radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = radius * 2.0;
    return 0;
}

int main(void)
{
    char input[256];
    char *end = NULL;
    double radius;
    double diameter;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || calculate_diameter(radius, &diameter) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", diameter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}