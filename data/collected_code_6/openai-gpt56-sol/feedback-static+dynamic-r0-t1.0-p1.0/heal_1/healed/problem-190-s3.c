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

static int is_inside_or_on_square(const Point square[4], Point p)
{
    int has_positive = 0;
    int has_negative = 0;

    for (size_t i = 0; i < 4; ++i) {
        const __int128 value =
            cross(square[i], square[(i + 1U) % 4U], p);

        has_positive |= value > 0;
        has_negative |= value < 0;

        if (has_positive && has_negative) {
            return 0;
        }
    }

    return 1;
}

static int count_integral_coordinates(const Point square[4],
                                      unsigned long long *count)
{
    long long min_x;
    long long max_x;
    long long min_y;
    long long max_y;
    unsigned long long result = 0;

    if (count == NULL) {
        return 0;
    }

    min_x = max_x = square[0].x;
    min_y = max_y = square[0].y;

    for (size_t i = 1; i < 4; ++i) {
        if (square[i].x < min_x) {
            min_x = square[i].x;
        } else if (square[i].x > max_x) {
            max_x = square[i].x;
        }

        if (square[i].y < min_y) {
            min_y = square[i].y;
        } else if (square[i].y > max_y) {
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

static void swap_points(Point *a, Point *b)
{
    const Point temporary = *a;
    *a = *b;
    *b = temporary;
}

static int is_square(const Point points[4], Point ordered[4])
{
    __int128 distances[6];
    size_t index = 0;

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = i + 1; j < 4; ++j) {
            const __int128 dx = (__int128)points[i].x - points[j].x;
            const __int128 dy = (__int128)points[i].y - points[j].y;
            distances[index++] = dx * dx + dy * dy;
        }
    }

    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = i + 1; j < 6; ++j) {
            if (distances[j] < distances[i]) {
                const __int128 temporary = distances[i];
                distances[i] = distances[j];
                distances[j] = temporary;
            }
        }
    }

    if (distances[0] <= 0 ||
        distances[0] != distances[1] ||
        distances[1] != distances[2] ||
        distances[2] != distances[3] ||
        distances[4] != distances[5] ||
        distances[4] != 2 * distances[0]) {
        return 0;
    }

    for (size_t i = 0; i < 4; ++i) {
        ordered[i] = points[i];
    }

    for (size_t i = 1; i < 4; ++i) {
        const __int128 dx_i =
            (__int128)ordered[i].x - ordered[0].x;
        const __int128 dy_i =
            (__int128)ordered[i].y - ordered[0].y;
        const __int128 distance_i = dx_i * dx_i + dy_i * dy_i;

        if (distance_i == distances[4]) {
            swap_points(&ordered[i], &ordered[3]);
            break;
        }
    }

    if (cross(ordered[0], ordered[1], ordered[2]) < 0) {
        swap_points(&ordered[1], &ordered[2]);
    }

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