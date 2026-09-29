#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int find_vertex(double a, double b, double c, double *x, double *y)
{
    if (x == NULL || y == NULL || !isfinite(a) || !isfinite(b) ||
        !isfinite(c) || a == 0.0) {
        return 0;
    }

    *x = -b / (2.0 * a);
    *y = fma(a, *x * *x, fma(b, *x, c));

    return isfinite(*x) && isfinite(*y);
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double result;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    result = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' || !isfinite(result)) {
        return 0;
    }

    *value = result;
    return 1;
}

int main(int argc, const char *const argv[])
{
    double a;
    double b;
    double c;
    double x;
    double y;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
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

    printf("Vertex: (%.17g, %.17g)\n", x, y);
    return EXIT_SUCCESS;
}