#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

int find_parabola_focus(double a, double b, double c, Point *focus)
{
    if (focus == NULL) {
        return -1;
    }
    if (fabs(a) < 1e-12) {
        return -1;
    }
    focus->x = -b / (2.0 * a);
    focus->y = c - (b * b) / (4.0 * a) + 1.0 / (4.0 * a);
    return 0;
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    double c = 0.0;
    Point focus = {0.0, 0.0};

    printf("Enter coefficients a, b, c of parabola y = ax^2 + bx + c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (find_parabola_focus(a, b, c, &focus) != 0) {
        fprintf(stderr, "Error: coefficient 'a' must be non-zero.\n");
        return EXIT_FAILURE;
    }

    printf("Focus of the parabola: (%.6f, %.6f)\n", focus.x, focus.y);

    return EXIT_SUCCESS;
}