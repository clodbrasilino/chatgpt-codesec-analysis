#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <math.h>
#include <ctype.h>
#include <limits.h>

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

static int read_line(char **buffer)
{
    size_t length = 0U;
    size_t capacity = 128U;
    int ch;
    char *line;

    if (buffer == NULL) {
        return 0;
    }

    *buffer = NULL;
    line = malloc(capacity);
    if (line == NULL) {
        return 0;
    }

    while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {
        char *resized;

        if (length == SIZE_MAX - 1U) {
            free(line);
            return 0;
        }

        if (length + 1U >= capacity) {
            size_t new_capacity;

            if (capacity > SIZE_MAX / 2U) {
                new_capacity = SIZE_MAX;
            } else {
                new_capacity = capacity * 2U;
            }

            if (new_capacity <= length + 1U) {
                free(line);
                return 0;
            }

            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return 0;
            }

            line = resized;
            capacity = new_capacity;
        }

        line[length++] = (char)ch;
    }

    if (ch == EOF && (ferror(stdin) || length == 0U)) {
        free(line);
        return 0;
    }

    line[length] = '\0';
    *buffer = line;
    return 1;
}

static int read_double(double *value)
{
    char *buffer;
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