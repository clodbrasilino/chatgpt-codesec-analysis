#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <ctype.h>

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
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end = NULL;
    double radius;
    double diameter;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || calculate_diameter(radius, &diameter) != 0) {
        free(input);
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", diameter);
    free(input);
    return EXIT_SUCCESS;
}