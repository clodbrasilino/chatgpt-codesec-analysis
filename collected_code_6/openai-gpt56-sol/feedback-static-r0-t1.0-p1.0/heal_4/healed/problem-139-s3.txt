#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int calculate_circumference(double radius, double *circumference)
{
    const double pi = 3.14159265358979323846;

    if (circumference == NULL || !isfinite(radius) || radius < 0.0) {
        return -1;
    }

    if (radius > DBL_MAX / (2.0 * pi)) {
        return -1;
    }

    *circumference = 2.0 * pi * radius;
    return 0;
}

static int read_line(char *buffer, size_t size)
{
    int ch;

    if (buffer == NULL || size < 2 || fgets(buffer, size, stdin) == NULL) {
        return -1;
    }

    for (size_t i = 0; i < size; ++i) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            return 0;
        }

        if (buffer[i] == '\0') {
            ch = fgetc(stdin);

            if (ch == '\n' || ch == EOF) {
                return 0;
            }

            do {
                ch = fgetc(stdin);
            } while (ch != '\n' && ch != EOF);

            return -1;
        }
    }

    return -1;
}

int main(void)
{
    char input[256];
    char *end;
    double radius;
    double circumference;

    if (read_line(input, sizeof input) != 0) {
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        return EXIT_FAILURE;
    }

    while (*end == ' ' || *end == '\t' || *end == '\r' ||
           *end == '\v' || *end == '\f') {
        ++end;
    }

    if (*end != '\0') {
        return EXIT_FAILURE;
    }

    if (calculate_circumference(radius, &circumference) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", circumference) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}