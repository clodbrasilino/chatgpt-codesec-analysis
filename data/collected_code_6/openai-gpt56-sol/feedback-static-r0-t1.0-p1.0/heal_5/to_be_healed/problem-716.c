#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int rhombus_perimeter(double side, double *perimeter)
{
    if (perimeter == NULL || !isfinite(side) ||
        side <= 0.0 || side > DBL_MAX / 4.0) {
        return -1;
    }

    *perimeter = 4.0 * side;
    return 0;
}

int main(void)
{
    double side;
    double perimeter;
    int result;
    int ch;

    fputs("Enter the side length of the rhombus: ", stdout);

    if (fflush(stdout) == EOF) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    result = scanf("%lf", &side);

    if (result != 1 || errno == ERANGE) {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    do {
        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        ch = getchar();
    } while (ch == ' ' || ch == '\t' || ch == '\v' ||
             ch == '\f' || ch == '\r');

    if (ch != '\n' && ch != EOF) {
        while (ch != '\n' && ch != EOF) {
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = getchar();
        }

        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (rhombus_perimeter(side, &perimeter) != 0) {
        fputs("Side length must be a finite positive number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        fputs("Failed to write output.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}