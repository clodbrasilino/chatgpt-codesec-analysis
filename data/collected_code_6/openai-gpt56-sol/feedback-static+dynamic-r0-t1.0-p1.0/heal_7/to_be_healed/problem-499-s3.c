#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL || !isfinite(radius) ||
        radius < 0.0 || radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = radius * 2.0;
    return 0;
}

static int read_radius(double *radius)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    /* Possible weaknesses found:
     *  The scope of the variable 'ch' can be reduced. [variableScope]
     */
    int ch;

    if (radius == NULL) {
        return -1;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    for (end = input; *end != '\0' && *end != '\n'; ++end) {
    }

    if (*end == '\0') {
        /* Possible weaknesses found:
         * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = fgetc(stdin);

        if (ch != '\n' && ch != EOF) {
            do {
                /* Possible weaknesses found:
                 * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
                 */
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return -2;
        }
    }

    errno = 0;
    end = NULL;
    *radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    return 0;
}

int main(void)
{
    double radius;
    double diameter;
    int status;

    status = read_radius(&radius);

    if (status == -2) {
        fputs("Input is too large.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status != 0 || calculate_diameter(radius, &diameter) != 0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", diameter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}