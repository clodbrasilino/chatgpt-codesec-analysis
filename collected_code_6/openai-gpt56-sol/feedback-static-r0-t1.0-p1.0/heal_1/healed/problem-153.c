#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Vertex;

static int find_parabola_vertex(double a, double b, double c, Vertex *vertex)
{
    if (vertex == NULL || !isfinite(a) || !isfinite(b) ||
        !isfinite(c) || a == 0.0) {
        return -1;
    }

    vertex->x = -b / (2.0 * a);
    vertex->y = c - (b * b) / (4.0 * a);

    if (!isfinite(vertex->x) || !isfinite(vertex->y)) {
        return -1;
    }

    return 0;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    *value = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' ||
        !isfinite(*value)) {
        return -1;
    }

    return 0;
}

int main(int argc, char *const argv[])
{
    double a;
    double b;
    double c;
    Vertex vertex;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &a) != 0 ||
        parse_double(argv[2], &b) != 0 ||
        parse_double(argv[3], &c) != 0) {
        fprintf(stderr, "All coefficients must be finite numbers.\n");
        return EXIT_FAILURE;
    }

    if (find_parabola_vertex(a, b, c, &vertex) != 0) {
        fprintf(stderr,
                "Unable to calculate the vertex; ensure a is nonzero.\n");
        return EXIT_FAILURE;
    }

    if (printf("Vertex: (%.17g, %.17g)\n", vertex.x, vertex.y) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}