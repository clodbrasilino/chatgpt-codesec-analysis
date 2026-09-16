#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int pentagon_perimeter(const double sides[static 5], double *result)
{
    double perimeter = 0.0;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < 5; ++i) {
        if (!isfinite(sides[i]) || sides[i] <= 0.0) {
            return -1;
        }

        perimeter += sides[i];

        if (!isfinite(perimeter)) {
            return -1;
        }
    }

    *result = perimeter;
    return 0;
}

int main(void)
{
    double sides[5];
    double perimeter;

    for (size_t i = 0; i < 5; ++i) {
        char input[128];
        char *end = NULL;

        if (fgets(input, sizeof input, stdin) == NULL) {
            fputs("Failed to read input.\n", stderr);
            return EXIT_FAILURE;
        }

        errno = 0;
        sides[i] = strtod(input, &end);

        if (end == input || errno == ERANGE || !isfinite(sides[i]) ||
            sides[i] <= 0.0) {
            fputs("Each side must be a positive finite number.\n", stderr);
            return EXIT_FAILURE;
        }

        while (*end == ' ' || *end == '\t') {
            ++end;
        }

        if (*end != '\n' && *end != '\0') {
            fputs("Invalid input.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (pentagon_perimeter(sides, &perimeter) != 0) {
        fputs("Unable to calculate the perimeter.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Perimeter: %.2f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}