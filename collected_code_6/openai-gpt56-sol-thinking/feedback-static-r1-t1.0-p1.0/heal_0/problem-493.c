#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HEXAGON_POINT_COUNT 6

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point points[HEXAGON_POINT_COUNT];
} Hexagon;

typedef struct {
    size_t rows;
    size_t columns;
    size_t count;
    Hexagon *hexagons;
} HexagonGrid;

void free_hexagon_grid(HexagonGrid *grid)
{
    if (grid != NULL) {
        free(grid->hexagons);
        free(grid);
    }
}

HexagonGrid *calculate_hexagon_grid(size_t rows,
                                    size_t columns,
                                    double radius,
                                    double origin_x,
                                    double origin_y)
{
    static const double x_factors[HEXAGON_POINT_COUNT] = {
        1.0, 0.5, -0.5, -1.0, -0.5, 0.5
    };
    static const double y_factors[HEXAGON_POINT_COUNT] = {
        0.0, 0.8660254037844386, 0.8660254037844386,
        0.0, -0.8660254037844386, -0.8660254037844386
    };

    HexagonGrid *grid;
    size_t count;
    double horizontal_spacing;
    double vertical_spacing;

    if (!isfinite(radius) || radius <= 0.0 ||
        !isfinite(origin_x) || !isfinite(origin_y)) {
        return NULL;
    }

    if (columns != 0 && rows > SIZE_MAX / columns) {
        return NULL;
    }

    count = rows * columns;

    if (count > SIZE_MAX / sizeof(Hexagon)) {
        return NULL;
    }

    horizontal_spacing = 1.5 * radius;
    vertical_spacing = sqrt(3.0) * radius;

    if (!isfinite(horizontal_spacing) || !isfinite(vertical_spacing)) {
        return NULL;
    }

    grid = calloc(1, sizeof(*grid));
    if (grid == NULL) {
        return NULL;
    }

    grid->rows = rows;
    grid->columns = columns;
    grid->count = count;

    if (count == 0) {
        return grid;
    }

    grid->hexagons = calloc(count, sizeof(*grid->hexagons));
    if (grid->hexagons == NULL) {
        free_hexagon_grid(grid);
        return NULL;
    }

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            size_t index = row * columns + column;
            double center_x = origin_x + (double)column * horizontal_spacing;
            double row_offset = (column % 2U == 0U) ? 0.0 : 0.5;
            double center_y = origin_y +
                              ((double)row + row_offset) * vertical_spacing;

            if (!isfinite(center_x) || !isfinite(center_y)) {
                free_hexagon_grid(grid);
                return NULL;
            }

            for (size_t point = 0; point < HEXAGON_POINT_COUNT; ++point) {
                double x = center_x + radius * x_factors[point];
                double y = center_y + radius * y_factors[point];

                if (!isfinite(x) || !isfinite(y)) {
                    free_hexagon_grid(grid);
                    return NULL;
                }

                grid->hexagons[index].points[point].x = x;
                grid->hexagons[index].points[point].y = y;
            }
        }
    }

    return grid;
}

int print_hexagon_grid(const HexagonGrid *grid)
{
    if (grid == NULL || (grid->count != 0 && grid->hexagons == NULL)) {
        return -1;
    }

    if (printf("[\n") < 0) {
        return -1;
    }

    for (size_t index = 0; index < grid->count; ++index) {
        if (printf("  [") < 0) {
            return -1;
        }

        for (size_t point = 0; point < HEXAGON_POINT_COUNT; ++point) {
            const Point *coordinate = &grid->hexagons[index].points[point];

            if (printf("(%.6f, %.6f)%s",
                       coordinate->x,
                       coordinate->y,
                       point + 1U == HEXAGON_POINT_COUNT ? "" : ", ") < 0) {
                return -1;
            }
        }

        if (printf("]%s\n", index + 1U == grid->count ? "" : ",") < 0) {
            return -1;
        }
    }

    return printf("]\n") < 0 ? -1 : 0;
}

int main(void)
{
    HexagonGrid *grid = calculate_hexagon_grid(3, 4, 10.0, 0.0, 0.0);

    if (grid == NULL) {
        return EXIT_FAILURE;
    }

    if (print_hexagon_grid(grid) != 0) {
        free_hexagon_grid(grid);
        return EXIT_FAILURE;
    }

    free_hexagon_grid(grid);
    return EXIT_SUCCESS;
}