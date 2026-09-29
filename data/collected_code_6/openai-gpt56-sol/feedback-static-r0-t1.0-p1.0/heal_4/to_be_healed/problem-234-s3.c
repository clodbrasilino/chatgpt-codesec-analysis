#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double side;
    double volume;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the side length.\n", stderr);
        return EXIT_FAILURE;
    }

    {
        size_t length = 0;

        while (length < sizeof input && input[length] != '\0') {
            ++length;
        }

        if (length == sizeof input) {
            fputs("Invalid input.\n", stderr);
            return EXIT_FAILURE;
        }

        if (length == 0 || input[length - 1] != '\n') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            int ch = fgetc(stdin);

            if (ch != '\n' && ch != EOF) {
                do {
                    /* Possible weaknesses found:
                     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                     */
                    ch = fgetc(stdin);
                } while (ch != '\n' && ch != EOF);

                fputs("Input is too long.\n", stderr);
                return EXIT_FAILURE;
            }
        }
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

    if (*end != '\0') {
        fputs("Invalid trailing input.\n", stderr);
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