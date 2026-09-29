#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_volume(double side, double *volume)
{
    double result;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    result = side * side * side;
    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

int main(void)
{
    char *input = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double side;
    double volume;

    errno = 0;
    length = getline(&input, &capacity, stdin);

    if (length < 0) {
        free(input);
        fputs("Failed to read the side length.\n", stderr);
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

    if (*end != '\0' || cube_volume(side, &volume) != 0) {
        free(input);
        fputs("Side length must be a finite, nonnegative value whose volume is representable.\n",
              stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.17g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}