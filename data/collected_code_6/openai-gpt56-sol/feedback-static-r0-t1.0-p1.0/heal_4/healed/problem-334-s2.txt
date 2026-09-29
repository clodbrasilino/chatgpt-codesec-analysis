#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int is_valid_triangle(double a, double b, double c)
{
    if (!isfinite(a) || !isfinite(b) || !isfinite(c)) {
        return 0;
    }

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    return a > fabs(b - c) && c > a - b && b > a - c;
}

static int parse_sides(double sides[3])
{
    for (size_t i = 0; i < 3; ++i) {
        char *line = NULL;
        size_t capacity = 0;
        ssize_t length;
        char *cursor;
        char *end;

        length = getline(&line, &capacity, stdin);
        if (length < 0) {
            free(line);
            return 0;
        }

        cursor = line;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        errno = 0;
        sides[i] = strtod(cursor, &end);

        if (end == cursor || errno == ERANGE) {
            free(line);
            return 0;
        }

        cursor = end;

        while (isspace((unsigned char)*cursor)) {
            ++cursor;
        }

        if (*cursor != '\0') {
            free(line);
            return 0;
        }

        free(line);
    }

    return 1;
}

int main(void)
{
    double sides[3];

    if (!parse_sides(sides)) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_valid_triangle(sides[0], sides[1], sides[2])
             ? "Valid triangle"
             : "Invalid triangle");

    return EXIT_SUCCESS;
}