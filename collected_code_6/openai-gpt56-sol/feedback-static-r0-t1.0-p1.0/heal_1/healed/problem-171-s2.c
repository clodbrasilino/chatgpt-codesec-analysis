#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIDE_COUNT 5
#define INPUT_SIZE 128

static int pentagon_perimeter(const double sides[static SIDE_COUNT],
                              double *result)
{
    double perimeter = 0.0;

    if (result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
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

static int read_side(double *side)
{
    char input[INPUT_SIZE];
    char *end;
    int ch;

    if (side == NULL || fgets(input, sizeof input, stdin) == NULL) {
        return -1;
    }

    if (input[0] != '\0' && input[strlen(input) - 1] != '\n') {
        ch = getchar();
        if (ch != '\n' && ch != EOF) {
            while ((ch = getchar()) != '\n' && ch != EOF) {
            }
            return -1;
        }
    }

    errno = 0;
    end = NULL;
    *side = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(*side) || *side <= 0.0) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    return *end == '\0' ? 0 : -1;
}

int main(void)
{
    double sides[SIDE_COUNT];
    double perimeter;

    for (size_t i = 0; i < SIDE_COUNT; ++i) {
        if (read_side(&sides[i]) != 0) {
            fputs("Each side must be a positive finite number.\n", stderr);
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