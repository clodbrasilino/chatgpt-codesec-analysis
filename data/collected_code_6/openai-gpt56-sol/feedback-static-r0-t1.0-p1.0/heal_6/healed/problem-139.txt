#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    const double pi = acos(-1.0);

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    if (radius > DBL_MAX / (2.0 * pi)) {
        return -1;
    }

    *circumference = 2.0 * pi * radius;

    return isfinite(*circumference) ? 0 : -1;
}

static int read_radius(double *radius)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double value;

    if (radius == NULL) {
        return -1;
    }

    errno = 0;
    length = getline(&line, &capacity, stdin);

    if (length < 0) {
        free(line);
        return -1;
    }

    if (ferror(stdin)) {
        free(line);
        return -1;
    }

    errno = 0;
    value = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(value) || value < 0.0) {
        free(line);
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return -1;
    }

    *radius = value;
    free(line);
    return 0;
}

int main(void)
{
    double radius;
    double circumference;

    if (read_radius(&radius) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_circumference(radius, &circumference) != 0) {
        fputs("Unable to calculate the circumference.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}