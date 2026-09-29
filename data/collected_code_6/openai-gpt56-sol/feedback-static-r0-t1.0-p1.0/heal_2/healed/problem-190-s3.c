#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x;
    long long y;
} Point;

static __int128 cross(Point a, Point b, Point p)
{
    const __int128 ab_x = (__int128)b.x - a.x;
    const __int128 ab_y = (__int128)b.y - a.y;
    const __int128 ap_x = (__int128)p.x - a.x;
    const __int128 ap_y = (__int128)p.y - a.y;

    return ab_x * ap_y - ab_y * ap_x;
}

static int compare_points(const void *lhs, const void *rhs)
{
    const Point *a = lhs;
    const Point *b = rhs;

    if (a->x < b->x) {
        return -1;
    }
    if (a->x > b->x) {
        return 1;
    }
    if (a->y < b->y) {
        return -1;
    }
    if (a->y > b->y) {
        return 1;
    }

    return 0;
}

static void order_vertices(const Point input[4], Point ordered[4])
{
    Point sorted[4];

    for (size_t i = 0; i < 4; ++i) {
        sorted[i] = input[i];
    }

    qsort(sorted, 4, sizeof sorted[0], compare_points);

    ordered[0] = sorted[0];

    if (cross(sorted[0], sorted[1], sorted[2]) > 0) {
        ordered[1] = sorted[1];
        ordered[2] = sorted[3];
        ordered[3] = sorted[2];
    } else {
        ordered[1] = sorted[2];
        ordered[2] = sorted[3];
        ordered[3] = sorted[1];
    }
}

static __int128 squared_distance(Point a, Point b)
{
    const __int128 dx = (__int128)b.x - a.x;
    const __int128 dy = (__int128)b.y - a.y;

    return dx * dx + dy * dy;
}

static int is_square(const Point points[4], Point ordered[4])
{
    order_vertices(points, ordered);

    const __int128 side0 = squared_distance(ordered[0], ordered[1]);
    const __int128 side1 = squared_distance(ordered[1], ordered[2]);
    const __int128 side2 = squared_distance(ordered[2], ordered[3]);
    const __int128 side3 = squared_distance(ordered[3], ordered[0]);
    const __int128 diagonal0 = squared_distance(ordered[0], ordered[2]);
    const __int128 diagonal1 = squared_distance(ordered[1], ordered[3]);

    return side0 > 0 &&
           side0 == side1 &&
           side1 == side2 &&
           side2 == side3 &&
           diagonal0 == diagonal1 &&
           diagonal0 == 2 * side0;
}

static int is_inside_or_on_square(const Point square[4], Point p)
{
    int has_positive = 0;
    int has_negative = 0;

    for (size_t i = 0; i < 4; ++i) {
        const __int128 value =
            cross(square[i], square[(i + 1U) % 4U], p);

        if (value > 0) {
            has_positive = 1;
        } else if (value < 0) {
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
    long long min_x = LLONG_MAX;
    long long max_x = LLONG_MIN;
    long long min_y = LLONG_MAX;
    long long max_y = LLONG_MIN;
    unsigned long long result = 0;

    for (size_t i = 0; i < 4; ++i) {
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

    for (long long y = min_y;;) {
        for (long long x = min_x;;) {
            if (is_inside_or_on_square(square, (Point){x, y})) {
                if (result == ULLONG_MAX) {
                    return 0;
                }
                ++result;
            }

            if (x == max_x) {
                break;
            }
            ++x;
        }

        if (y == max_y) {
            break;
        }
        ++y;
    }

    *count = result;
    return 1;
}

int main(void)
{
    Point input[4];
    Point square[4];
    unsigned long long count;

    for (size_t i = 0; i < 4; ++i) {
        if (scanf("%lld %lld", &input[i].x, &input[i].y) != 2) {
            fputs("Invalid input\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (!is_square(input, square)) {
        fputs("The coordinates do not form a square\n", stderr);
        return EXIT_FAILURE;
    }

    if (!count_integral_coordinates(square, &count)) {
        fputs("Count overflow\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%llu\n", count) < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}