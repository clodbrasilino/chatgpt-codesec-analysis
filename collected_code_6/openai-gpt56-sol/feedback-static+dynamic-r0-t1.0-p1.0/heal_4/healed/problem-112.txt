#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    const double pi = acos(-1.0);
    double value;

    if (result == NULL ||
        !isfinite(radius) ||
        !isfinite(height) ||
        radius < 0.0 ||
        height < 0.0) {
        return -1;
    }

    value = 2.0 * (2.0 * pi * radius + height);

    if (!isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

static int parse_double(const char **input, double *value)
{
    char *end;

    if (input == NULL || *input == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)**input)) {
        ++*input;
    }

    if (**input == '\0') {
        return -1;
    }

    errno = 0;
    *value = strtod(*input, &end);

    if (end == *input || errno == ERANGE || !isfinite(*value)) {
        return -1;
    }

    *input = end;
    return 0;
}

int main(void)
{
    char buffer[256];
    const char *input;
    double radius;
    double height;
    double perimeter;
    int ch;

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(buffer, '\n') == NULL) {
        ch = fgetc(stdin);
        if (ch != '\n' && ch != EOF) {
            return EXIT_FAILURE;
        }
    }

    input = buffer;

    if (parse_double(&input, &radius) != 0 ||
        parse_double(&input, &height) != 0) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*input)) {
        ++input;
    }

    if (*input != '\0') {
        return EXIT_FAILURE;
    }

    if (cylinder_perimeter(radius, height, &perimeter) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.6f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}