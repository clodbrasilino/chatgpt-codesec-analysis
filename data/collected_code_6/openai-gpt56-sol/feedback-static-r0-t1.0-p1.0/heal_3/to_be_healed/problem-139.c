#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    const double pi = acos(-1.0);

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    if (radius > DBL_MAX / (2.0 * pi)) {
        return -1;
    }

    *circumference = 2.0 * pi * radius;
    return 0;
}

int main(void)
{
    double radius;
    double circumference;
    int ch;

    if (scanf("%lf", &radius) != 1) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = getchar()) != EOF) {
        if (ch != ' ' && ch != '\t' && ch != '\n' &&
            ch != '\r' && ch != '\f' && ch != '\v') {
            fputs("Invalid radius.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (ferror(stdin) || !isfinite(radius) || radius < 0.0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    if (calculate_circumference(radius, &circumference) != 0) {
        fputs("Unable to calculate the circumference.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}