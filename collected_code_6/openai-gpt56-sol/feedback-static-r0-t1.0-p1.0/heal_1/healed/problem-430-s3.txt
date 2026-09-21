#include <ctype.h>
#include <errno.h>
#include <math.h>
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

static int discard_line_remainder(void) {
    int ch;

    do {
        ch = getchar();
    } while (ch != '\n' && ch != EOF);

    return ch == '\n' ? 0 : -1;
}

static int read_double(const char *prompt, double *value) {
    char buffer[256];
    char *end;
    double parsed;
    size_t length;

    if (prompt == NULL || value == NULL) {
        return -1;
    }

    if (fputs(prompt, stdout) == EOF || fflush(stdout) == EOF) {
        return -1;
    }

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        return -1;
    }

    length = 0;
    while (length < sizeof buffer && buffer[length] != '\0') {
        ++length;
    }

    if (length == sizeof buffer) {
        return -1;
    }

    if (length > 0 && buffer[length - 1] != '\n' && !feof(stdin)) {
        discard_line_remainder();
        return -1;
    }

    errno = 0;
    parsed = strtod(buffer, &end);

    if (end == buffer || errno == ERANGE || !isfinite(parsed)) {
        return -1;
    }

    while (*end != '\0' && isspace((unsigned char)*end)) {
        ++end;
    }

    if (*end != '\0') {
        return -1;
    }

    *value = parsed;
    return 0;
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