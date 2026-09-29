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

static int discard_line(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
    }

    return ferror(stdin) ? -1 : 0;
}

static int read_double(double *value)
{
    char buffer[256];
    char *start;
    char *end;
    size_t length;
    double parsed;

    if (value == NULL) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return -1;
    }

    if (length > 0 && buffer[length - 1] != '\n' && !feof(stdin)) {
        if (discard_line() != 0) {
            return -1;
        }
    }

    start = buffer;
    while (isspace((unsigned char)*start)) {
        ++start;
    }

    if (*start == '\0') {
        return -1;
    }

    errno = 0;
    end = NULL;
    parsed = strtod(start, &end);

    if (end == start ||
        end == NULL ||
        errno == ERANGE ||
        !isfinite(parsed)) {
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
}

static int only_trailing_whitespace(void)
{
    int ch;

    while ((ch = fgetc(stdin)) != EOF) {
        if (!isspace((unsigned char)ch)) {
            return 0;
        }
    }

    return ferror(stdin) ? 0 : 1;
}

int main(void)
{
    double radius;
    double height;
    double perimeter;

    if (read_double(&radius) != 0 ||
        read_double(&height) != 0 ||
        !only_trailing_whitespace()) {
        return EXIT_FAILURE;
    }

    if (cylinder_perimeter(radius, height, &perimeter) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.10g\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}