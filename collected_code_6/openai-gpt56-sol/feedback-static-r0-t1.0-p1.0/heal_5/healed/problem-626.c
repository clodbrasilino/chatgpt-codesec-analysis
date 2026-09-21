#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_inscribed_triangle(double radius, double *area)
{
    const double coefficient = 3.0 * sqrt(3.0) / 4.0;
    double result;

    if (area == NULL || !isfinite(radius) || radius <= 0.0) {
        return -1;
    }

    if (radius > sqrt(DBL_MAX / coefficient)) {
        return -1;
    }

    result = coefficient * radius * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double area;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end == '\n') {
        *end = '\0';
    } else if (!feof(stdin)) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            fputs("Failed to read the radius.\n", stderr);
        } else {
            fputs("Input is too long.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || largest_inscribed_triangle(radius, &area) != 0) {
        fputs("Radius must be a finite positive number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Largest triangle area: %.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}