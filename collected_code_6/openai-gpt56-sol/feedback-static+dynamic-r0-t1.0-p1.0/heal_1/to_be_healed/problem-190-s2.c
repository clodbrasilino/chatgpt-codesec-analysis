#include <errno.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t x;
    int64_t y;
} Point;

static int64_t cross(Point a, Point b, Point p)
{
    return (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);
}

static int point_inside_square(const Point square[4], Point p)
{
    int64_t first = cross(square[0], square[1], p);
    int64_t second = cross(square[1], square[2], p);
    int64_t third = cross(square[2], square[3], p);
    int64_t fourth = cross(square[3], square[0], p);

    return ((first >= 0 && second >= 0 && third >= 0 && fourth >= 0) ||
            (first <= 0 && second <= 0 && third <= 0 && fourth <= 0));
}

static int count_integral_points(const Point square[4], uint64_t *count)
{
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'. [duplicateAssignExpression]
     */
    int64_t min_x = square[0].x;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_x' and 'max_x'.
     */
    int64_t max_x = square[0].x;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'. [duplicateAssignExpression]
     */
    int64_t min_y = square[0].y;
    /* Possible weaknesses found:
     *  Same expression used in consecutive assignments of 'min_y' and 'max_y'.
     */
    int64_t max_y = square[0].y;
    size_t i;

    if (count == NULL) {
        return 0;
    }

    for (i = 1; i < 4; ++i) {
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

    *count = 0;

    for (int64_t x = min_x;; ++x) {
        for (int64_t y = min_y;; ++y) {
            Point p = {x, y};

            if (point_inside_square(square, p)) {
                if (*count == UINT64_MAX) {
                    return 0;
                }
                ++(*count);
            }

            if (y == max_y) {
                break;
            }
        }

        if (x == max_x) {
            break;
        }
    }

    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end = NULL;
    intmax_t parsed;

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno != 0 || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    Point square[4];
    uint64_t count;
    size_t i;

    if (argc != 9) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2 x3 y3 x4 y4\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 0; i < 4; ++i) {
        if (!parse_int64(argv[2 * i + 1], &square[i].x) ||
            !parse_int64(argv[2 * i + 2], &square[i].y)) {
            fputs("Invalid coordinate\n", stderr);
            return EXIT_FAILURE;
        }
    }

    if (!count_integral_points(square, &count)) {
        fputs("Unable to count integral points\n", stderr);
        return EXIT_FAILURE;
    }

    printf("%" PRIu64 "\n", count);
    return EXIT_SUCCESS;
}