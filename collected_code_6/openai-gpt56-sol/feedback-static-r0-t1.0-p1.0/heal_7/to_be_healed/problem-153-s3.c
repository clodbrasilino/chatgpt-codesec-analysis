#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_vertex(double a, double b, double c, double *x, double *y)
{
    double vertex_x;
    double vertex_y;

    if (x == NULL || y == NULL ||
        !isfinite(a) || !isfinite(b) || !isfinite(c) ||
        a == 0.0) {
        return 0;
    }

    vertex_x = -0.5 * (b / a);
    if (!isfinite(vertex_x)) {
        return 0;
    }

    vertex_y = fma(vertex_x, fma(a, vertex_x, b), c);
    if (!isfinite(vertex_y)) {
        return 0;
    }

    *x = vertex_x;
    *y = vertex_y;

    return 1;
}

static int parse_double(const char *text, double *value)
{
    char *end;
    double parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' || !isfinite(parsed)) {
        return 0;
    }

    *value = parsed;

    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char * const argv[])
{
    double a;
    double b;
    double c;
    double x;
    double y;
    const char *program_name = "program";

    if (argc > 0 && argv != NULL && argv[0] != NULL) {
        program_name = argv[0];
    }

    if (argc != 4 || argv == NULL) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", program_name);
        return EXIT_FAILURE;
    }

    if (!parse_double(argv[1], &a) ||
        !parse_double(argv[2], &b) ||
        !parse_double(argv[3], &c)) {
        fputs("Invalid coefficient.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_vertex(a, b, c, &x, &y)) {
        fputs("Unable to calculate the vertex.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Vertex: (%.17g, %.17g)\n", x, y) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}