#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_volume(double side, double *volume)
{
    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    *volume = side * side * side;

    if (!isfinite(*volume)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    char input[256];
    char *end = NULL;
    double side;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the side length.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || cube_volume(side, &volume) != 0) {
        fprintf(stderr, "Side length must be a finite, nonnegative value whose volume is representable.\n");
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}