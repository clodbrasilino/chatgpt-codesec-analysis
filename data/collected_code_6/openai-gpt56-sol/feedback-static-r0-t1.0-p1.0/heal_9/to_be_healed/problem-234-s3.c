#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cube_volume(double side, double *volume)
{
    double limit;
    double result;

    if (volume == NULL || !isfinite(side) || side < 0.0) {
        return -1;
    }

    limit = cbrt(DBL_MAX);
    if (side > limit) {
        return -1;
    }

    result = side * side * side;
    if (!isfinite(result)) {
        return -1;
    }

    *volume = result;
    return 0;
}

static void discard_line(void)
{
    int ch;

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

static int read_side(double *side)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;

    if (side == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        discard_line();
        return 1;
    }

    errno = 0;
    *side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return 2;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 2;
    }

    return 0;
}

int main(void)
{
    double side;
    double volume;
    int status;

    status = read_side(&side);

    if (status < 0) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 1) {
        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status == 2) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (cube_volume(side, &volume) != 0) {
        fputs("The side length must be finite, nonnegative, and within range.\n",
              stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}