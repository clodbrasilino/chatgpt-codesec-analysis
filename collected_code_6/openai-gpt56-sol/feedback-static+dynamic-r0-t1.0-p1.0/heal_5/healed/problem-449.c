#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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

static int read_line(char **line)
{
    enum { INITIAL_CAPACITY = 128 };
    size_t length = 0;
    size_t capacity = INITIAL_CAPACITY;
    char *buffer;
    int ch = EOF;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc(capacity);
    if (buffer == NULL) {
        return 0;
    }

    for (;;) {
        ch = fgetc(stdin);

        if (ch == '\n' || ch == EOF) {
            break;
        }

        if (length == capacity - 1) {
            size_t new_capacity;
            char *new_buffer;

            if (capacity > SIZE_MAX / 2) {
                free(buffer);
                return 0;
            }

            new_capacity = capacity * 2;
            new_buffer = realloc(buffer, new_capacity);
            if (new_buffer == NULL) {
                free(buffer);
                return 0;
            }

            buffer = new_buffer;
            capacity = new_capacity;
        }

        buffer[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0)) {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *line = buffer;
    return 1;
}

static int read_double(double *value)
{
    char *buffer = NULL;
    char *start;
    char *end;
    double parsed;

    if (value == NULL || !read_line(&buffer)) {
        return 0;
    }

    start = buffer;
    while (*start != '\0' && isspace((unsigned char)*start)) {
        ++start;
    }

    errno = 0;
    parsed = strtod(start, &end);

    if (end == start || errno == ERANGE || !isfinite(parsed)) {
        free(buffer);
        return 0;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        free(buffer);
        return 0;
    }

    *value = parsed;
    free(buffer);
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

    if (is_valid_triangle(points[0], points[1], points[2])) {
        puts("Valid triangle");
    } else {
        puts("Invalid triangle");
    }

    return EXIT_SUCCESS;
}