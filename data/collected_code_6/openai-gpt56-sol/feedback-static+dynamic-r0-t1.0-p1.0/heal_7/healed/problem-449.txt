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

static int discard_line(void)
{
    int ch;

    do {
        ch = fgetc(stdin);
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' || !ferror(stdin);
}

static int read_line(char **line)
{
    enum {
        MAX_LINE_LENGTH = 4096
    };

    char *buffer;
    size_t length = 0;
    int ch;

    if (line == NULL) {
        return 0;
    }

    *line = NULL;
    buffer = malloc((size_t)MAX_LINE_LENGTH + 1U);
    if (buffer == NULL) {
        return 0;
    }

    while (length < (size_t)MAX_LINE_LENGTH) {
        ch = fgetc(stdin);

        if (ch == '\n') {
            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        if (ch == EOF) {
            if (ferror(stdin) || length == 0U) {
                free(buffer);
                return 0;
            }

            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        buffer[length++] = (char)ch;
    }

    ch = fgetc(stdin);
    if (ch == '\n') {
        buffer[length] = '\0';
        *line = buffer;
        return 1;
    }

    if (ch == EOF) {
        if (!ferror(stdin)) {
            buffer[length] = '\0';
            *line = buffer;
            return 1;
        }

        free(buffer);
        return 0;
    }

    (void)discard_line();
    free(buffer);
    return 0;
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

    for (i = 0; i < 3U; ++i) {
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