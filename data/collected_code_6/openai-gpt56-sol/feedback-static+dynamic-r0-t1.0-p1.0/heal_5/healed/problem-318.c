#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int maximum_cuboid_volume(double side_sum, double *volume)
{
    double side;
    double limit;

    if (volume == NULL || !isfinite(side_sum) || side_sum < 0.0) {
        return -1;
    }

    side = side_sum / 3.0;
    limit = cbrt(DBL_MAX);

    if (side > limit) {
        return -1;
    }

    *volume = side * side * side;

    return isfinite(*volume) ? 0 : -1;
}

static int read_side_sum(double *side_sum)
{
    char input[256];
    char *end;

    if (side_sum == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return -1;
    }

    errno = 0;
    *side_sum = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return -1;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    return *end == '\0' ? 0 : -1;
}

int main(void)
{
    double side_sum;
    double volume;

    if (read_side_sum(&side_sum) != 0 ||
        maximum_cuboid_volume(side_sum, &volume) != 0) {
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}