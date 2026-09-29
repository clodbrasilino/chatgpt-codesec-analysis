#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int cylinder_perimeter(double radius, double height, double *result)
{
    double value;

    if (result == NULL || !isfinite(radius) || !isfinite(height) ||
        radius < 0.0 || height < 0.0) {
        return -1;
    }

    value = 2.0 * (2.0 * acos(-1.0) * radius + height);
    if (!isfinite(value)) {
        return -1;
    }

    *result = value;
    return 0;
}

static int read_double(const char **cursor, double *value)
{
    char *end;

    if (cursor == NULL || *cursor == NULL || value == NULL) {
        return -1;
    }

    while (isspace((unsigned char)**cursor)) {
        ++*cursor;
    }

    errno = 0;
    *value = strtod(*cursor, &end);

    if (end == *cursor || errno == ERANGE || !isfinite(*value)) {
        return -1;
    }

    *cursor = end;
    return 0;
}

int main(void)
{
    char input[256];
    const char *cursor;
    double radius;
    double height;
    double perimeter;

    if (fgets(input, sizeof input, stdin) == NULL) {
        return EXIT_FAILURE;
    }

    if (strchr(input, '\n') == NULL && !feof(stdin)) {
        int ch;

        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);

        return EXIT_FAILURE;
    }

    cursor = input;

    if (read_double(&cursor, &radius) != 0 ||
        read_double(&cursor, &height) != 0) {
        return EXIT_FAILURE;
    }

    while (isspace((unsigned char)*cursor)) {
        ++cursor;
    }

    if (*cursor != '\0' ||
        cylinder_perimeter(radius, height, &perimeter) != 0) {
        return EXIT_FAILURE;
    }

    if (printf("%.6f\n", perimeter) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}