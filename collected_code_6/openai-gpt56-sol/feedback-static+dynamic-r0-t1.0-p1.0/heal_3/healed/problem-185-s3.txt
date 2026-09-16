#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

static int find_parabola_focus(double a, double h, double k, Point *focus)
{
    if (focus == NULL || !isfinite(a) || !isfinite(h) ||
        !isfinite(k) || a == 0.0) {
        return 0;
    }

    const double offset = 1.0 / (4.0 * a);
    const double focus_y = k + offset;

    if (!isfinite(offset) || !isfinite(focus_y)) {
        return 0;
    }

    focus->x = h;
    focus->y = focus_y;
    return 1;
}

static int parse_double(const char *text, double *value)
{
    if (text == NULL || value == NULL) {
        return 0;
    }

    char *end = NULL;
    errno = 0;
    const double result = strtod(text, &end);

    if (errno != 0 || end == text || *end != '\0' || !isfinite(result)) {
        return 0;
    }

    *value = result;
    return 1;
}

int main(int argc, char *const argv[])
{
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <a> <h> <k>\n", argv[0]);
        return EXIT_FAILURE;
    }

    double a;
    double h;
    double k;
    Point focus;

    if (!parse_double(argv[1], &a) ||
        !parse_double(argv[2], &h) ||
        !parse_double(argv[3], &k)) {
        fputs("Invalid numeric input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (!find_parabola_focus(a, h, k, &focus)) {
        fputs("Unable to calculate the focus.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("Focus: (%.17g, %.17g)\n", focus.x, focus.y) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}