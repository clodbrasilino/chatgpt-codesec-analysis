#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL || !isfinite(radius) ||
        radius < 0.0 || radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = 2.0 * radius;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    char *end = NULL;
    double radius;
    double diameter;

    if (getline(&input, &capacity, stdin) == -1) {
        fputs("Failed to read the radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || calculate_diameter(radius, &diameter) != 0) {
        fputs("Invalid radius.\n", stderr);
        free(input);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", diameter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}