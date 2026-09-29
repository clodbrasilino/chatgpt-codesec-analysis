#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x;
    long long y;
} Point;

static __int128 cross(Point a, Point b, Point p)
{
    return (__int128)(b.x - a.x) * (p.y - a.y) -
           (__int128)(b.y - a.y) * (p.x - a.x);
}

static int is_inside_or_on_square(const Point square[4], Point p)
{
    int has_positive = 0;
    int has_negative = 0;

    for (size_t i = 0; i < 4; ++i) {
        const __int128 value = cross(square[i], square[(i + 1U) % 4U], p);
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
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'. [duplicateAssignExpression]
     */
    long long min_x = square[0].x;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     */
    long long max_x = square[0].x;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'. [duplicateAssignExpression]
     */
    long long min_y = square[0].y;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     */
    long long max_y = square[0].y;
    unsigned long long result = 0;

    for (size_t i = 1; i < 4; ++i) {
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

    for (long long y = min_y;; ++y) {
        for (long long x = min_x;; ++x) {
            if (is_inside_or_on_square(square, (Point){x, y})) {
                if (result == ULLONG_MAX) {
                    return 0;
                }
                ++result;
            }

            if (x == max_x) {
                break;
            }
        }

        if (y == max_y) {
            break;
        }
    }

    *count = result;
    return 1;
}

static int is_square(const Point points[4], Point ordered[4])
{
    double center_x = 0.0;
    double center_y = 0.0;

    for (size_t i = 0; i < 4; ++i) {
        center_x += (double)points[i].x;
        center_y += (double)points[i].y;
        ordered[i] = points[i];
    }

    center_x /= 4.0;
    center_y /= 4.0;

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = i + 1; j < 4; ++j) {
            const double angle_i =
                atan2((double)ordered[i].y - center_y,
                      (double)ordered[i].x - center_x);
            const double angle_j =
                atan2((double)ordered[j].y - center_y,
                      (double)ordered[j].x - center_x);

            if (angle_j < angle_i) {
                const Point temporary = ordered[i];
                ordered[i] = ordered[j];
                ordered[j] = temporary;
            }
        }
    }

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

    return distances[0] > 0 &&
           distances[0] == distances[1] &&
           distances[1] == distances[2] &&
           distances[2] == distances[3] &&
           distances[4] == distances[5] &&
           distances[4] == 2 * distances[0];
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