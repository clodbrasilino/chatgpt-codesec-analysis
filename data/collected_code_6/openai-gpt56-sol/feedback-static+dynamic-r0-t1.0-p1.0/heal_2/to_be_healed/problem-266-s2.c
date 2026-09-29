#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cube_lateral_surface_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    if (side > sqrt(DBL_MAX / 4.0)) {
        return -1;
    }

    *area = 4.0 * side * side;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double side;
    double area;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || cube_lateral_surface_area(side, &area) != 0) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", area) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}