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

    length = strlen(input);

    if (length > 0 && input[length - 1] == '\n') {
        input[length - 1] = '\0';
    } else if (!feof(stdin)) {
        int ch;

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