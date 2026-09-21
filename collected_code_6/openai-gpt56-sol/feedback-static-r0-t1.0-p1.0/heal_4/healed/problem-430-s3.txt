#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double a;
    double b;
    double c;
} Directrix;

int find_parabola_directrix(
    double vertex_x,
    double vertex_y,
    double axis_x,
    double axis_y,
    double focal_distance,
    Directrix *directrix
) {
    double magnitude;
    double c;

    if (directrix == NULL ||
        !isfinite(vertex_x) ||
        !isfinite(vertex_y) ||
        !isfinite(axis_x) ||
        !isfinite(axis_y) ||
        !isfinite(focal_distance) ||
        focal_distance == 0.0) {
        return -1;
    }

    magnitude = hypot(axis_x, axis_y);
    if (!isfinite(magnitude) || magnitude == 0.0) {
        return -1;
    }

    axis_x /= magnitude;
    axis_y /= magnitude;

    if (focal_distance < 0.0) {
        focal_distance = -focal_distance;
        axis_x = -axis_x;
        axis_y = -axis_y;
    }

    c = focal_distance - axis_x * vertex_x - axis_y * vertex_y;
    if (!isfinite(c)) {
        return -1;
    }

    directrix->a = axis_x;
    directrix->b = axis_y;
    directrix->c = c;

    return 0;
}

static int read_line(FILE *stream, char **line, size_t *capacity) {
    size_t length = 0;

    if (stream == NULL || line == NULL || capacity == NULL) {
        return -1;
    }

    if (*line == NULL || *capacity < 2) {
        size_t initial_capacity = 128;
        char *allocated = malloc(initial_capacity);

        if (allocated == NULL) {
            return -1;
        }

        free(*line);
        *line = allocated;
        *capacity = initial_capacity;
    }

    for (;;) {
        int ch = fgetc(stream);

        if (ch == '\n') {
            break;
        }

        if (ch == EOF) {
            if (ferror(stream) || length == 0) {
                return -1;
            }
            break;
        }

        if (length == *capacity - 1) {
            size_t new_capacity;
            char *resized;

            if (*capacity > SIZE_MAX / 2) {
                return -1;
            }

            new_capacity = *capacity * 2;
            resized = realloc(*line, new_capacity);
            if (resized == NULL) {
                return -1;
            }

            *line = resized;
            *capacity = new_capacity;
        }

        (*line)[length++] = (char)ch;
    }

    (*line)[length] = '\0';
    return 0;
}

static int read_double(const char *prompt, double *value) {
    char *line = NULL;
    char *end;
    double parsed;
    size_t capacity = 0;
    int result = -1;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (read_line(stdin, &line, &capacity) != 0) {
        free(line);
        return -1;
    }

    errno = 0;
    parsed = strtod(line, &end);

    if (end != line && errno != ERANGE && isfinite(parsed)) {
        while (*end != '\0' && isspace((unsigned char)*end)) {
            ++end;
        }

        if (*end == '\0') {
            *value = parsed;
            result = 0;
        }
    }

    free(line);
    return result;
}

int main(void) {
    double vertex_x;
    double vertex_y;
    double axis_x;
    double axis_y;
    double focal_distance;
    Directrix directrix;

    if (read_double("Vertex x: ", &vertex_x) != 0 ||
        read_double("Vertex y: ", &vertex_y) != 0 ||
        read_double("Axis direction x: ", &axis_x) != 0 ||
        read_double("Axis direction y: ", &axis_y) != 0 ||
        read_double("Signed focal distance: ", &focal_distance) != 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (find_parabola_directrix(
            vertex_x,
            vertex_y,
            axis_x,
            axis_y,
            focal_distance,
            &directrix) != 0) {
        fputs("Unable to determine the directrix.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf(
            "Directrix: %.17g*x %+.17g*y %+.17g = 0\n",
            directrix.a,
            directrix.b,
            directrix.c) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}