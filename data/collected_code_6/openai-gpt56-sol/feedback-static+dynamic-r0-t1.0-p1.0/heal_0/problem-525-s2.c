#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} Point;

static bool lines_are_parallel(Point a1, Point a2, Point b1, Point b2, bool *valid)
{
    const double epsilon = 1e-12;
    const double dx1 = a2.x - a1.x;
    const double dy1 = a2.y - a1.y;
    const double dx2 = b2.x - b1.x;
    const double dy2 = b2.y - b1.y;
    const double length1 = hypot(dx1, dy1);
    const double length2 = hypot(dx2, dy2);
    double cross;
    double scale;

    if (valid == NULL) {
        return false;
    }

    *valid = false;

    if (!isfinite(length1) || !isfinite(length2) ||
        length1 <= epsilon || length2 <= epsilon) {
        return false;
    }

    cross = dx1 * dy2 - dy1 * dx2;
    scale = length1 * length2;

    if (!isfinite(cross) || !isfinite(scale) || scale == 0.0) {
        return false;
    }

    *valid = true;
    return fabs(cross) <= epsilon * scale;
}

int main(void)
{
    Point a1;
    Point a2;
    Point b1;
    Point b2;
    bool valid;
    bool parallel;

    if (scanf("%lf %lf %lf %lf %lf %lf %lf %lf",
              &a1.x, &a1.y, &a2.x, &a2.y,
              &b1.x, &b1.y, &b2.x, &b2.y) != 8) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    parallel = lines_are_parallel(a1, a2, b1, b2, &valid);

    if (!valid) {
        fputs("Invalid line\n", stderr);
        return 1;
    }

    puts(parallel ? "Parallel" : "Not parallel");
    return 0;
}