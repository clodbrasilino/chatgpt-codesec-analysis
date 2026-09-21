#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int rhombus_area(double diagonal1, double diagonal2, double *area)
{
    if (area == NULL || !isfinite(diagonal1) || !isfinite(diagonal2) ||
        diagonal1 <= 0.0 || diagonal2 <= 0.0) {
        return 0;
    }

    *area = (diagonal1 / 2.0) * diagonal2;

    return isfinite(*area);
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end = NULL;
    double diagonal1;
    double diagonal2;
    double area;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the first diagonal.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    diagonal1 = strtod(input, &end);
    if (end == input || errno == ERANGE) {
        fputs("Invalid first diagonal.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid first diagonal.\n", stderr);
        return EXIT_FAILURE;
    }

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the second diagonal.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    diagonal2 = strtod(input, &end);
    if (end == input || errno == ERANGE) {
        fputs("Invalid second diagonal.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t') {
        ++end;
    }

    if (*end != '\n' && *end != '\0') {
        fputs("Invalid second diagonal.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!rhombus_area(diagonal1, diagonal2, &area)) {
        fputs("Diagonals must be positive finite numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.2f\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}