#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    const double pi = acos(-1.0);
    double value;

    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    value = 2.0 * (2.0 * pi * radius + height);
    if (!isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

static int read_number(double *value)
{
    char token[256];
    size_t length = 0;
    int ch;
    char *end;

    if (value == NULL) {
        return -1;
    }

    do {
        ch = fgetc(stdin);
    } while (ch != EOF && isspace((unsigned char)ch));

    if (ch == EOF) {
        return -1;
    }

    do {
        if (length + 1 >= sizeof token) {
            do {
                ch = fgetc(stdin);
            } while (ch != EOF && !isspace((unsigned char)ch));
            return -1;
        }

        token[length++] = (char)ch;
        ch = fgetc(stdin);
    } while (ch != EOF && !isspace((unsigned char)ch));

    token[length] = '\0';

    errno = 0;
    *value = strtod(token, &end);

    if (end == token || *end != '\0' || errno == ERANGE ||
        !isfinite(*value)) {
        return -1;
    }

    return 0;
}

static int only_whitespace_remains(void)
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

    if (read_number(&radius) != 0 ||
        read_number(&height) != 0 ||
        !only_whitespace_remains()) {
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