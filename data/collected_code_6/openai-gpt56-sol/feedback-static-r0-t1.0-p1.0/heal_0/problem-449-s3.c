#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} Point;

static bool is_valid_triangle(Point a, Point b, Point c)
{
    const double area_twice =
        (a.x * (b.y - c.y)) +
        (b.x * (c.y - a.y)) +
        (c.x * (a.y - b.y));

    return isfinite(area_twice) && area_twice != 0.0;
}

int main(void)
{
    Point a;
    Point b;
    Point c;

    if (scanf("%lf %lf %lf %lf %lf %lf",
              &a.x, &a.y, &b.x, &b.y, &c.x, &c.y) != 6) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!isfinite(a.x) || !isfinite(a.y) ||
        !isfinite(b.x) || !isfinite(b.y) ||
        !isfinite(c.x) || !isfinite(c.y)) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    puts(is_valid_triangle(a, b, c) ? "Valid triangle" : "Invalid triangle");

    return 0;
}