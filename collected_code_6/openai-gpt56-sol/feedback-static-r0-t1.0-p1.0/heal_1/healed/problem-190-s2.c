#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int64_t x;
    int64_t y;
} Point;

static int cross(Point a, Point b, Point p, int64_t *result)
{
    int64_t ab_x;
    int64_t ab_y;
    int64_t ap_x;
    int64_t ap_y;
    int64_t lhs;
    int64_t rhs;

    if (result == NULL ||
        __builtin_sub_overflow(b.x, a.x, &ab_x) ||
        __builtin_sub_overflow(b.y, a.y, &ab_y) ||
        __builtin_sub_overflow(p.x, a.x, &ap_x) ||
        __builtin_sub_overflow(p.y, a.y, &ap_y) ||
        __builtin_mul_overflow(ab_x, ap_y, &lhs) ||
        __builtin_mul_overflow(ab_y, ap_x, &rhs) ||
        __builtin_sub_overflow(lhs, rhs, result)) {
        return 0;
    }

    return 1;
}

static int point_inside_square(const Point square[static 4], Point p, int *inside)
{
    int64_t products[4];
    size_t i;
    int all_nonnegative = 1;
    int all_nonpositive = 1;

    if (inside == NULL) {
        return 0;
    }

    for (i = 0; i < 4; ++i) {
        if (!cross(square[i], square[(i + 1U) % 4U], p, &products[i])) {
            return 0;
        }

        if (products[i] < 0) {
            all_nonnegative = 0;
        }
        if (products[i] > 0) {
            all_nonpositive = 0;
        }
    }

    *inside = all_nonnegative || all_nonpositive;
    return 1;
}

static int count_integral_points(const Point square[static 4], uint64_t *count)
{
    int64_t min_x;
    int64_t max_x;
    int64_t min_y;
    int64_t max_y;
    int64_t x;
    size_t i;

    if (count == NULL) {
        return 0;
    }

    min_x = max_x = square[0].x;
    min_y = max_y = square[0].y;

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
    x = min_x;

    for (;;) {
        int64_t y = min_y;

        for (;;) {
            Point p = {x, y};
            int inside;

            if (!point_inside_square(square, p, &inside)) {
                return 0;
            }

            if (inside) {
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

    if (text == NULL || value == NULL) {
        return 0;
    }

    errno = 0;
    end = NULL;
    parsed = strtoimax(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' ||
        parsed < INT64_MIN || parsed > INT64_MAX) {
        return 0;
    }

    *value = (int64_t)parsed;
    return 1;
}

int main(int argc, char *const argv[])
{
    Point square[4];
    uint64_t count;
    size_t i;

    if (argc != 9) {
        fprintf(stderr, "Usage: %s x1 y1 x2 y2 x3 y3 x4 y4\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (i = 0; i < 4; ++i) {
        if (!parse_int64(argv[2U * i + 1U], &square[i].x) ||
            !parse_int64(argv[2U * i + 2U], &square[i].y)) {
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