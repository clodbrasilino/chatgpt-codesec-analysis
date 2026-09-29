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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end = NULL;
    double side;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the cube's side length.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid trailing input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_volume(side, &volume) != 0) {
        fputs("The side length must be finite, nonnegative, and within range.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        fputs("Failed to write the result.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}