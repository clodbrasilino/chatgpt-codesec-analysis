#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_area(double side, double *area)
{
    if (area == NULL || !isfinite(side) || side <= 0.0) {
        return -1;
    }

    *area = 0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0))) * side * side;

    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[256];
    char *end = NULL;
    double side;
    double area;

    printf("Enter the side length of a regular pentagon: ");

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

    if (*end != '\0') {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    if (pentagon_area(side, &area) != 0) {
        fputs("The side length must be a finite positive number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Area: %.6f\n", area);

    return EXIT_SUCCESS;
}