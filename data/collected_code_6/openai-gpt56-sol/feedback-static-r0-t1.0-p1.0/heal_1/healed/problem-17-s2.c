#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int square_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    if (side > DBL_MAX / 4.0) {
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
    char *end = NULL;
    double side;
    double perimeter;

    length = getline(&input, &capacity, stdin);
    if (length < 0) {
        free(input);
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (errno == ERANGE || end == input) {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\n' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0') {
        free(input);
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (square_perimeter(side, &perimeter) != 0) {
        fputs("Side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}