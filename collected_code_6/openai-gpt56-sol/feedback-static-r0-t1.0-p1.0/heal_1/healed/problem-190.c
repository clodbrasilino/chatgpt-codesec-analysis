#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long double x;
    long double y;
} Point;

static long double cross(Point a, Point b, Point p)
{
    return (b.x - a.x) * (p.y - a.y) -
           (b.y - a.y) * (p.x - a.x);
}

static int is_inside_or_on(const Point square[4], Point p)
{
    int has_positive = 0;
    int has_negative = 0;
    size_t i;

    for (i = 0U; i < 4U; ++i) {
        long double value =
            cross(square[i], square[(i + 1U) % 4U], p);

        if (value > 0.0L) {
            has_positive = 1;
        } else if (value < 0.0L) {
            has_negative = 1;
        }

        if (has_positive && has_negative) {
            return 0;
        }
    }

    return 1;
}

static int count_integral_coordinates(const Point square[4],
                                      unsigned long long *count)
{
    long double min_x;
    long double max_x;
    long double min_y;
    long double max_y;
    long double rounded;
    long long start_x;
    long long end_x;
    long long start_y;
    long long end_y;
    long long x;
    size_t i;

    if (square == NULL || count == NULL) {
        return 0;
    }

    if (!isfinite(square[0].x) || !isfinite(square[0].y)) {
        return 0;
    }

    min_x = square[0].x;
    max_x = square[0].x;
    min_y = square[0].y;
    max_y = square[0].y;

    for (i = 1U; i < 4U; ++i) {
        if (!isfinite(square[i].x) || !isfinite(square[i].y)) {
            return 0;
        }

        if (square[i].x < min_x) {
            min_x = square[i].x;
        }
        if (square[i].x > max_x) {
            max_x = square[i].x;
        }
        if (square[i].y < min_y) {
            min_y = square[i].y;
        }
        if (square[i].y > max_y) {
            max_y = square[i].y;
        }
    }

    rounded = ceill(min_x);
    if (rounded < (long double)LLONG_MIN ||
        rounded > (long double)LLONG_MAX) {
        return 0;
    }
    start_x = (long long)rounded;

    rounded = floorl(max_x);
    if (rounded < (long double)LLONG_MIN ||
        rounded > (long double)LLONG_MAX) {
        return 0;
    }
    end_x = (long long)rounded;

    rounded = ceill(min_y);
    if (rounded < (long double)LLONG_MIN ||
        rounded > (long double)LLONG_MAX) {
        return 0;
    }
    start_y = (long long)rounded;

    rounded = floorl(max_y);
    if (rounded < (long double)LLONG_MIN ||
        rounded > (long double)LLONG_MAX) {
        return 0;
    }
    end_y = (long long)rounded;

    *count = 0ULL;

    if (start_x > end_x || start_y > end_y) {
        return 1;
    }

    x = start_x;
    for (;;) {
        long long y = start_y;

        for (;;) {
            Point p = {(long double)x, (long double)y};

            if (is_inside_or_on(square, p)) {
                if (*count == ULLONG_MAX) {
                    return 0;
                }
                ++*count;
            }

            if (y == end_y) {
                break;
            }
            ++y;
        }

        if (x == end_x) {
            break;
        }
        ++x;
    }

    return 1;
}

int main(void)
{
    Point square[4];
    unsigned long long count;
    size_t i;

    for (i = 0U; i < 4U; ++i) {
        if (scanf("%Lf %Lf", &square[i].x, &square[i].y) != 2) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (!count_integral_coordinates(square, &count)) {
        fputs("Unable to count integral coordinates\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}