#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

static int find_parabola_focus(double a, double b, double c, Point *focus)
{
    double x;
    double y;

    if (focus == NULL || !isfinite(a) || !isfinite(b) ||
        !isfinite(c) || a == 0.0) {
        return 0;
    }

    x = -b / (2.0 * a);
    y = c - (b * b) / (4.0 * a) + 1.0 / (4.0 * a);

    if (!isfinite(x) || !isfinite(y)) {
        return 0;
    }

    focus->x = x;
    focus->y = y;
    return 1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed;

    if (text == NULL || value == NULL) {
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

int main(int argc, const char *argv[])
{
    double a;
    double b;
    double c;
    Point focus;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (!parse_double(argv[1], &a) ||
        !parse_double(argv[2], &b) ||
        !parse_double(argv[3], &c)) {
        fputs("Error: coefficients must be finite numbers.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_parabola_focus(a, b, c, &focus)) {
        fputs("Error: invalid parabola or unrepresentable focus.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Focus: (%.17g, %.17g)\n", focus.x, focus.y) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}