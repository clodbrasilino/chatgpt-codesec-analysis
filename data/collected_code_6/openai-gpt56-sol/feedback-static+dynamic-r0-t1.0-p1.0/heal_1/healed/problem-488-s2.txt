#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_area(double side, double *area)
{
    const double factor = 0.25 * sqrt(5.0 * (5.0 + 2.0 * sqrt(5.0)));

    if (area == NULL || !isfinite(side) || side <= 0.0) {
        return -1;
    }

    if (side > sqrt(DBL_MAX / factor)) {
        return -1;
    }

    *area = factor * side * side;
    return isfinite(*area) ? 0 : -1;
}

int main(void)
{
    char input[256];
    char *end;
    double side;
    double area;
    int ch;

    printf("Enter the side length of a regular pentagon: ");
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fprintf(stderr, "Failed to read input.\n");
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
        fprintf(stderr, "Input is too long.\n");
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fprintf(stderr, "Invalid side length.\n");
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        fprintf(stderr, "Unexpected input after the side length.\n");
        return EXIT_FAILURE;
    }

    if (pentagon_area(side, &area) != 0) {
        fprintf(stderr, "The side length must produce a finite positive area.\n");
        return EXIT_FAILURE;
    }

    printf("Area: %.6f\n", area);
    return EXIT_SUCCESS;
}