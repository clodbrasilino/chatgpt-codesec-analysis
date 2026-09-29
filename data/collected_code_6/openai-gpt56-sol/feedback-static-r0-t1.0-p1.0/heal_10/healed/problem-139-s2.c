#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int circle_circumference(double radius, double *circumference)
{
    const double pi = acos(-1.0);

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    if (radius > DBL_MAX / (2.0 * pi)) {
        return -1;
    }

    *circumference = 2.0 * pi * radius;
    return 0;
}

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ferror(stdin) ? -1 : 0;
}

static int read_radius(double *radius)
{
    enum { INPUT_SIZE = 256 };
    char input[INPUT_SIZE];
    char *end;
    double value;

    if (radius == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    char *newline = strchr(input, '\n');

    if (newline != NULL) {
        *newline = '\0';
    } else if (!feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
        return -1;
    }

    errno = 0;
    end = NULL;
    value = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(value)) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *radius = value;
    return 0;
}

int main(void)
{
    double radius;
    double circumference;

    if (read_radius(&radius) != 0) {
        return EXIT_FAILURE;
    }

    if (circle_circumference(radius, &circumference) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}