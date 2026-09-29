#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    double result;

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    result = 2.0 * acos(-1.0) * radius;

    if (!isfinite(result)) {
        return -1;
    }

    *circumference = result;
    return 0;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double circumference;
    int ch;

    if (fgets(input, sizeof input, stdin) == NULL) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        do {
            ch = fgetc(stdin);
        } while (ch != '\n' && ch != EOF);

        if (ferror(stdin)) {
            fputs("Failed to read the radius.\n", stderr);
        } else {
            fputs("Input is too large.\n", stderr);
        }

        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE || !isfinite(radius)) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\n' ||
           *end == '\r' || *end == '\f' || *end == '\v') {
        ++end;
    }

    if (*end != '\0' || radius < 0.0) {
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    if (calculate_circumference(radius, &circumference) != 0) {
        fputs("Unable to calculate the circumference.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}