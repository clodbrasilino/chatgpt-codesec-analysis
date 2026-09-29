#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int calculate_surface_area(double radius, double *area)
{
    const double pi = 3.14159265358979323846;
    double result;

    if (area == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = pi * radius * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *area = result;
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
    double area;
    size_t length;

    fputs("Enter the cylinder radius: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;

        /* Possible weaknesses found:
         * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
         */
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (radius < 0.0) {
        fputs("Radius must be a non-negative number.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_surface_area(radius, &area) != 0) {
        fputs("Unable to calculate the surface area.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Top or bottom surface area: %.10g\n", area);
    return EXIT_SUCCESS;
}