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
    if (focus == NULL || !isfinite(a) || !isfinite(b) ||
        !isfinite(c) || a == 0.0) {
        return 0;
    }

    const double h = -b / (2.0 * a);
    const double k = c - (b * b) / (4.0 * a);
    const double p = 1.0 / (4.0 * a);
    const double focus_y = k + p;

    if (!isfinite(h) || !isfinite(k) || !isfinite(p) ||
        !isfinite(focus_y)) {
        return 0;
    }

    focus->x = h;
    focus->y = focus_y;
    return 1;
}

static int parse_double(const char *text, double *value)
{
    char *end = NULL;
    double parsed_value;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed_value = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' ||
        !isfinite(parsed_value)) {
        return 0;
    }

    *value = parsed_value;
    return 1;
}

int main(int argc, char * const argv[])
{
    double a;
    double b;
    double c;
    Point focus;

    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <b> <c>\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "parabola");
        return EXIT_FAILURE;
    }

    if (!parse_double(argv[1], &a) ||
        !parse_double(argv[2], &b) ||
        !parse_double(argv[3], &c)) {
        fputs("Invalid coefficient\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_parabola_focus(a, b, c, &focus)) {
        fputs("Unable to determine the focus\n", stderr);
        return EXIT_FAILURE;
    }

    printf("Focus: (%.17g, %.17g)\n", focus.x, focus.y);
    return EXIT_SUCCESS;
}