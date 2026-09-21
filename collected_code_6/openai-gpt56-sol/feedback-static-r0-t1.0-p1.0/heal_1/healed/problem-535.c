#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

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
    int ch;

    printf("Enter the cylinder radius: ");
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read the radius.\n");
        return EXIT_FAILURE;
    }

    if (input[0] != '\0' && input[strlen(input) - 1] != '\n' && !feof(stdin)) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        fprintf(stderr, "Invalid radius.\n");
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' || radius < 0.0) {
        fprintf(stderr, "Radius must be a non-negative number.\n");
        return EXIT_FAILURE;
    }

    if (calculate_surface_area(radius, &area) != 0) {
        fprintf(stderr, "Unable to calculate the surface area.\n");
        return EXIT_FAILURE;
    }

    printf("Top or bottom surface area: %.10g\n", area);
    return EXIT_SUCCESS;
}