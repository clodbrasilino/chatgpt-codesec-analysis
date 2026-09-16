#include <math.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point start;
    Point end;
} Line;

static bool is_valid_line(const Line *line)
{
    if (line == NULL) {
        return false;
    }

    if (!isfinite(line->start.x) || !isfinite(line->start.y) ||
        !isfinite(line->end.x) || !isfinite(line->end.y)) {
        return false;
    }

    return line->start.x != line->end.x || line->start.y != line->end.y;
}

static bool are_parallel(const Line *first, const Line *second, bool *result)
{
    double first_dx;
    double first_dy;
    double second_dx;
    double second_dy;
    double cross_product;
    double tolerance;

    if (result == NULL || !is_valid_line(first) || !is_valid_line(second)) {
        return false;
    }

    first_dx = first->end.x - first->start.x;
    first_dy = first->end.y - first->start.y;
    second_dx = second->end.x - second->start.x;
    second_dy = second->end.y - second->start.y;

    if (!isfinite(first_dx) || !isfinite(first_dy) ||
        !isfinite(second_dx) || !isfinite(second_dy)) {
        return false;
    }

    cross_product = first_dx * second_dy - first_dy * second_dx;
    tolerance = 1e-12 * hypot(first_dx, first_dy) *
                hypot(second_dx, second_dy);

    if (!isfinite(cross_product) || !isfinite(tolerance)) {
        return false;
    }

    *result = fabs(cross_product) <= tolerance;
    return true;
}

int main(void)
{
    Line first;
    Line second;
    bool parallel;

    if (scanf("%lf %lf %lf %lf",
              &first.start.x, &first.start.y,
              &first.end.x, &first.end.y) != 4) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (scanf("%lf %lf %lf %lf",
              &second.start.x, &second.start.y,
              &second.end.x, &second.end.y) != 4) {
        fputs("Invalid input\n", stderr);
        return 1;
    }

    if (!are_parallel(&first, &second, &parallel)) {
        fputs("Invalid line data\n", stderr);
        return 1;
    }

    puts(parallel ? "Parallel" : "Not parallel");
    return 0;
}