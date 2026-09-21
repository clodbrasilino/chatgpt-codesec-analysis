#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    double result;

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = 2.0 * acos(-1.0) * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *circumference = result;
    return 0;
}

static int read_radius(double *radius)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;

    if (radius == NULL) {
        return -1;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return -1;
    }

    errno = 0;
    *radius = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(*radius)) {
        free(line);
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || *radius < 0.0) {
        free(line);
        return -1;
    }

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