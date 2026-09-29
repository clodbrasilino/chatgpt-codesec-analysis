#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>

typedef struct {
    double x;
    double y;
} Point;

static int is_valid_triangle(Point a, Point b, Point c)
{
    long double area;

    if (!isfinite(a.x) || !isfinite(a.y) ||
        !isfinite(b.x) || !isfinite(b.y) ||
        !isfinite(c.x) || !isfinite(c.y)) {
        return 0;
    }

    area = ((long double)b.x - (long double)a.x) *
           ((long double)c.y - (long double)a.y) -
           ((long double)b.y - (long double)a.y) *
           ((long double)c.x - (long double)a.x);

    return area != 0.0L;
}

static int read_double(double *value)
{
    char *line = NULL;
    size_t capacity = 0;
    ssize_t length;
    char *end;
    double parsed;

    if (value == NULL) {
        return 0;
    }

    length = getline(&line, &capacity, stdin);
    if (length < 0) {
        free(line);
        return 0;
    }

    errno = 0;
    parsed = strtod(line, &end);

    if (end == line || errno == ERANGE || !isfinite(parsed)) {
        free(line);
        return 0;
    }

    while (isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(line);
        return 0;
    }

    *value = parsed;
    free(line);
    return 1;
}

int main(void)
{
    Point points[3];
    size_t i;

    for (i = 0; i < 3; ++i) {
        if (!read_double(&points[i].x) ||
            !read_double(&points[i].y)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    puts(is_valid_triangle(points[0], points[1], points[2])
             ? "Valid triangle"
             : "Invalid triangle");

    return EXIT_SUCCESS;
}