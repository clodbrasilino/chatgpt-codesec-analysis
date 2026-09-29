#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_parabola_vertex(double a, double b, double c,
                                double *vertex_x, double *vertex_y)
{
    if (vertex_x == NULL || vertex_y == NULL ||
        !isfinite(a) || !isfinite(b) || !isfinite(c) || a == 0.0) {
        return -1;
    }

    const double x = -b / (2.0 * a);
    const double y = c - (b * b) / (4.0 * a);

    if (!isfinite(x) || !isfinite(y)) {
        return -1;
    }

    *vertex_x = x;
    *vertex_y = y;
    return 0;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;

    if (text == NULL || value == NULL) {
        return -1;
    }

    errno = 0;
    const double parsed = strtod(text, &end);

    if (errno == ERANGE || end == text || *end != '\0' || !isfinite(parsed)) {
        return -1;
    }

    *value = parsed;
    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    double a;
    double b;
    double c;
    double vertex_x;
    double vertex_y;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (parse_double(argv[1], &a) != 0 ||
        parse_double(argv[2], &b) != 0 ||
        parse_double(argv[3], &c) != 0) {
        fprintf(stderr, "Error: coefficients must be finite numbers.\n");
        return EXIT_FAILURE;
    }

    if (find_parabola_vertex(a, b, c, &vertex_x, &vertex_y) != 0) {
        fprintf(stderr, "Error: invalid parabola or unrepresentable vertex.\n");
        return EXIT_FAILURE;
    }

    printf("Vertex: (%.17g, %.17g)\n", vertex_x, vertex_y);
    return EXIT_SUCCESS;
}