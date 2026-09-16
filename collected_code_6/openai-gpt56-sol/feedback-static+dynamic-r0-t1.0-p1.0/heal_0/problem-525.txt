#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point start;
    Point end;
} Line;

static int lines_are_parallel(const Line *first, const Line *second, int *parallel)
{
    const double dx1 = first->end.x - first->start.x;
    const double dy1 = first->end.y - first->start.y;
    const double dx2 = second->end.x - second->start.x;
    const double dy2 = second->end.y - second->start.y;
    const double length1 = hypot(dx1, dy1);
    const double length2 = hypot(dx2, dy2);
    const double tolerance = 1e-12;

    if (!isfinite(length1) || !isfinite(length2) ||
        length1 <= tolerance || length2 <= tolerance) {
        return 0;
    }

    *parallel = fabs(dx1 * dy2 - dy1 * dx2) <=
                tolerance * length1 * length2;
    return 1;
}

int main(void)
{
    Line first;
    Line second;
    int parallel = 0;

    if (scanf("%lf %lf %lf %lf",
              &first.start.x, &first.start.y,
              &first.end.x, &first.end.y) != 4) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (scanf("%lf %lf %lf %lf",
              &second.start.x, &second.start.y,
              &second.end.x, &second.end.y) != 4) {
        fputs("Invalid input\n", stderr);
        return EXIT_FAILURE;
    }

    if (!lines_are_parallel(&first, &second, &parallel)) {
        fputs("Invalid line\n", stderr);
        return EXIT_FAILURE;
    }

    puts(parallel ? "Parallel" : "Not parallel");
    return EXIT_SUCCESS;
}