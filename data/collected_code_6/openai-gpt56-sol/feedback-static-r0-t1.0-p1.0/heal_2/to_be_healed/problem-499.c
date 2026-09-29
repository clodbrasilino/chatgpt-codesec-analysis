#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <ctype.h>

static int calculate_diameter(double radius, double *diameter)
{
    if (diameter == NULL || !isfinite(radius) ||
        radius < 0.0 || radius > DBL_MAX / 2.0) {
        return -1;
    }

    *diameter = 2.0 * radius;
    return 0;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end;
    double radius;
    double diameter;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || calculate_diameter(radius, &diameter) != 0) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    printf("%.17g\n", diameter);
    return EXIT_SUCCESS;
}