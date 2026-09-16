#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

static int is_valid_triangle(const Point *a, const Point *b, const Point *c)
{
    const long double area =
        ((long double)b->x - (long double)a->x) *
            ((long double)c->y - (long double)a->y) -
        ((long double)b->y - (long double)a->y) *
            ((long double)c->x - (long double)a->x);

    return isfinite(a->x) && isfinite(a->y) &&
           isfinite(b->x) && isfinite(b->y) &&
           isfinite(c->x) && isfinite(c->y) &&
           area != 0.0L;
}

int main(void)
{
    Point points[3];

    /* Possible weaknesses found:
     *  %lf in format string (no. 2) requires 'double *' but the argument type is 'double'. [invalidScanfArgType_float]
     *  %lf in format string (no. 1) requires 'double *' but the argument type is 'double'. [invalidScanfArgType_float]
     */
    if (scanf("%lf %lf %lf %lf %lf %lf",
              &points[0].x, &points[0].y,
              &points[1].x, &points[1].y,
              &points[2].x, &points[2].y) != 6) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    puts(is_valid_triangle(&points[0], &points[1], &points[2])
             ? "Valid triangle"
             : "Invalid triangle");

    return EXIT_SUCCESS;
}