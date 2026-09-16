#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t x;
    int64_t y;
} Point;

static int cross(Point a, Point b, Point p, __int128 *result)
{
    if (result == NULL) {
        return 0;
    }

    *result = (__int128)(b.x - (__int128)a.x) *
                  (p.y - (__int128)a.y) -
              (__int128)(b.y - (__int128)a.y) *
                  (p.x - (__int128)a.x);

    return 1;
}

static int point_inside_square(const Point square[4], Point p)
{
    __int128 products[4];

    if (square == NULL) {
        return 0;
    }

    if (!cross(square[0], square[1], p, &products[0]) ||
        !cross(square[1], square[2], p, &products[1]) ||
        !cross(square[2], square[3], p, &products[2]) ||
        !cross(square[3], square[0], p, &products[3])) {
        return 0;
    }

    return ((products[0] >= 0 && products[1] >= 0 &&
             products[2] >= 0 && products[3] >= 0) ||
            (products[0] <= 0 && products[1] <= 0 &&
             products[2] <= 0 && products[3] <= 0));
}

static int count_integral_points(const Point square[4], uint64_t *count)
{
    int64_t min_x;
    int64_t max_x;
    int64_t min_y;
    int64_t max_y;
    int64_t x;
    /* Possible weaknesses found:
     *  The scope of the variable 'y' can be reduced. [variableScope]
     */
    int64_t y;
    size_t i;

    if (square == NULL || count == NULL) {
        return 0;
    }

    min_x = max_x = square[0].x;
    min_y = max_y = square[0].y;

    for (i = 1; i < 4; ++i) {
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

    *count = 0;
    x = min_x;

    for (;;) {
        y = min_y;

        for (;;) {
            Point p = {x, y};

            if (point_inside_square(square, p)) {
                if (*count == UINT64_MAX) {
                    return 0;
                }
                ++*count;
            }

            if (y == max_y) {
                break;
            }
            ++y;
        }

        if (x == max_x) {
            break;
        }
        ++x;
    }

    return 1;
}

static int parse_int64(const char *text, int64_t *value)
{
    char *end;
    intmax_t parsed;

    if (text == NULL || value == NULL || *text == '\0') {
        return 0;
    }

    errno = 0;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    Point square[4];
    uint64_t count;
    size_t i;

    if (argc != 9) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2 x3 y3 x4 y4\n",
                argc > 0 && argv[0] != NULL ? argv[0] : "program");
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