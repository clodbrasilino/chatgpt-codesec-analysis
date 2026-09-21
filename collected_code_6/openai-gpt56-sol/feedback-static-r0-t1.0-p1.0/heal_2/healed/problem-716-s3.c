#include <ctype.h>
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
    char input[256];
    char extra[2];
    char *end;
    double side;
    double perimeter;

    fputs("Enter the side length of the rhombus: ", stdout);
    fflush(stdout);

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (sscanf(input, "%*255[^\n]%1[\n]", extra) == 0 &&
        input[0] != '\n' && !feof(stdin)) {
        int ch;

        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        }

        fputs("Input is too long.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    side = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        fputs("Invalid side length.\n", stderr);
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' ||
        rhombus_perimeter(side, &perimeter) != 0) {
        fputs("Side length must be a positive finite number.\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Perimeter: %.2f\n", perimeter);
    return EXIT_SUCCESS;
}