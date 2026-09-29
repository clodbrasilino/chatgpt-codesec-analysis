#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int rhombus_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL ||
        !isfinite(side) ||
        side <= 0.0 ||
        side > DBL_MAX / 4.0) {
        return -1;
    }

    *perimeter = 4.0 * side;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double side;
    double perimeter;

    if (fputs("Enter the side length of the rhombus: ", stdout) == EOF ||
        fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || rhombus_perimeter(side, &perimeter) != 0) {
        free(input);
        fputs("Side length must be a positive finite number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}