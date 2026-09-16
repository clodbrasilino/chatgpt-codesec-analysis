#include <errno.h>
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
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

static int is_inside_or_on(const Point square[4], Point p)
{
    int has_positive = 0;
    int has_negative = 0;
    size_t i;

    for (i = 0U; i < 4U; ++i) {
        long double value = cross(square[i], square[(i + 1U) % 4U], p);

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
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     *  Either the condition 'square==NULL' is redundant or there is possible null pointer dereference: square. [nullPointerRedundantCheck]
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'. [duplicateAssignExpression]
     *  Null pointer dereference
     */
    long double min_x = square[0].x;
    /* Possible weaknesses found:
     *  Either the condition 'square==NULL' is redundant or there is possible null pointer dereference: square. [nullPointerRedundantCheck]
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     *  Null pointer dereference
     */
    long double max_x = square[0].x;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'. [duplicateAssignExpression]
     *  Either the condition 'square==NULL' is redundant or there is possible null pointer dereference: square. [nullPointerRedundantCheck]
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     *  Null pointer dereference
     */
    long double min_y = square[0].y;
    /* Possible weaknesses found:
     *  Either the condition 'square==NULL' is redundant or there is possible null pointer dereference: square. [nullPointerRedundantCheck]
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     *  Null pointer dereference
     */
    long double max_y = square[0].y;
    long long start_x;
    long long end_x;
    long long start_y;
    long long end_y;
    long long x;
    size_t i;

    /* Possible weaknesses found:
     *  Assuming that condition 'square==NULL' is not redundant
     */
    if (square == NULL || count == NULL) {
        return 0;
    }

    for (i = 0U; i < 4U; ++i) {
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

    if (ceill(min_x) < (long double)LLONG_MIN ||
        floorl(max_x) > (long double)LLONG_MAX ||
        ceill(min_y) < (long double)LLONG_MIN ||
        floorl(max_y) > (long double)LLONG_MAX) {
        return 0;
    }

    start_x = (long long)ceill(min_x);
    end_x = (long long)floorl(max_x);
    start_y = (long long)ceill(min_y);
    end_y = (long long)floorl(max_y);
    *count = 0U;

    if (start_x > end_x || start_y > end_y) {
        return 1;
    }

    for (x = start_x;; ++x) {
        long long y;

        for (y = start_y;; ++y) {
            Point p = {(long double)x, (long double)y};

            if (is_inside_or_on(square, p)) {
                if (*count == ULLONG_MAX) {
                    return 0;
                }
                ++(*count);
            }

            if (y == end_y) {
                break;
            }
        }

        if (x == end_x) {
            break;
        }
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