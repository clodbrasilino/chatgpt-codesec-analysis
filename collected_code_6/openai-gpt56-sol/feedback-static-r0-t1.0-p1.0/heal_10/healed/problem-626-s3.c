#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int largest_inscribed_triangle(double radius, double *area)
{
    if (area == NULL || !isfinite(radius) || radius <= 0.0) {
        return -1;
    }

    if (radius > sqrt(DBL_MAX)) {
        return -1;
    }

    *area = radius * radius;
    return isfinite(*area) ? 0 : -1;
}

static int read_line(FILE *stream, char **buffer)
{
    size_t capacity = 128U;
    size_t length = 0U;
    char *line;

    if (stream == NULL || buffer == NULL) {
        return -1;
    }

    *buffer = NULL;
    line = malloc(capacity);
    if (line == NULL) {
        return -1;
    }

    for (;;) {
        int ch;

        if (length == capacity - 1U) {
            size_t new_capacity;
            char *resized;

            if (capacity > SIZE_MAX / 2U) {
                free(line);
                return -1;
            }

            new_capacity = capacity * 2U;
            resized = realloc(line, new_capacity);
            if (resized == NULL) {
                free(line);
                return -1;
            }

            line = resized;
            capacity = new_capacity;
        }

        ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0U) {
                free(line);
                return -1;
            }
            break;
        }

        line[length++] = (char)(unsigned char)ch;
    }

    line[length] = '\0';
    *buffer = line;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *end = NULL;
    double radius;
    double area;

    if (read_line(stdin, &input) != 0) {
        fputs("Failed to read the radius.\n", stderr);
        return EXIT_FAILURE;
    }

    errno = 0;
    radius = strtod(input, &end);

    if (end == input || errno == ERANGE) {
        free(input);
        fputs("Invalid radius.\n", stderr);
        return EXIT_FAILURE;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0' ||
        largest_inscribed_triangle(radius, &area) != 0) {
        free(input);
        fputs("Radius must be a positive finite number.\n", stderr);
        return EXIT_FAILURE;
    }

    free(input);

    if (printf("%.10g\n", area) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}