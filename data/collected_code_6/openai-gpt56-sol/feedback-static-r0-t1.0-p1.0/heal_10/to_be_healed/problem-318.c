#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int maximum_cuboid_volume(double side_sum, double *volume)
{
    double side;
    double limit;

    if (volume == NULL || !isfinite(side_sum) || side_sum < 0.0) {
        return -1;
    }

    side = side_sum / 3.0;
    limit = cbrt(DBL_MAX);

    if (!isfinite(side) || side > limit) {
        return -1;
    }

    *volume = side * side * side;

    return isfinite(*volume) ? 0 : -1;
}

int main(void)
{
    enum { INPUT_SIZE = 256 };
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[INPUT_SIZE];
    char *end;
    double side_sum;
    double volume;
    size_t length;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        ++length;
    }

    if (input[length] == '\n') {
        input[length] = '\0';
    } else {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
            }

            if (ch == EOF && ferror(stdin)) {
                fputs("Failed to read the sum of sides.\n", stderr);
            } else {
                fputs("Input is too large.\n", stderr);
            }

            return EXIT_FAILURE;
        }

        if (ch == EOF && ferror(stdin)) {
            fputs("Failed to read the sum of sides.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    errno = 0;
    side_sum = strtod(input, &end);

    if (errno == ERANGE || end == input) {
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || maximum_cuboid_volume(side_sum, &volume) != 0) {
        fputs("Invalid sum of sides.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.17g\n", volume) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}