#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
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

    return isfinite(area) && area != 0.0L;
}

static int read_line(char *buffer, size_t capacity)
{
    size_t length;

    if (buffer == NULL || capacity < 2U) {
        return 0;
    }

    if (fgets(buffer, (int)capacity, stdin) == NULL) {
        return 0;
    }

    length = 0U;
    while (buffer[length] != '\0' && buffer[length] != '\n') {
        ++length;
    }

    if (buffer[length] == '\n') {
        buffer[length] = '\0';
        return 1;
    }

    if (feof(stdin)) {
        return length != 0U;
    }

    for (;;) {
        char discard[256];

        if (fgets(discard, (int)sizeof discard, stdin) == NULL) {
            break;
        }

        length = 0U;
        while (discard[length] != '\0' && discard[length] != '\n') {
            ++length;
        }

        if (discard[length] == '\n') {
            break;
        }
    }

    return 0;
}

static int read_double(double *value)
{
    enum {
        LINE_CAPACITY = 4098
    };

    char buffer[LINE_CAPACITY];
    char *start;
    char *end;
    double parsed;

    if (value == NULL || !read_line(buffer, sizeof buffer)) {
        return 0;
    }

    start = buffer;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtod(start, &end);

    if (end == start || errno == ERANGE || !isfinite(parsed)) {
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return 0;
    }

    *value = parsed;
    return 1;
}

int main(void)
{
    Point points[3];
    size_t i;

    for (i = 0U; i < 3U; ++i) {
        if (!read_double(&points[i].x) ||
            !read_double(&points[i].y)) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (is_valid_triangle(points[0], points[1], points[2])) {
        puts("Valid triangle");
    } else {
        puts("Invalid triangle");
    }

    return EXIT_SUCCESS;
}