#include <errno.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

typedef struct {
    size_t rows;
    size_t columns;
    size_t count;
    Hexagon hexagons[];
} HexagonGrid;

HexagonGrid *calculate_hexagon_grid(size_t rows, size_t columns,
                                    double radius, double origin_x,
                                    double origin_y)
{
    const double sqrt_three = 1.73205080756887729353;
    HexagonGrid *grid;
    size_t count;
    size_t allocation_size;

    if (rows == 0 || columns == 0 || !isfinite(radius) || radius <= 0.0 ||
        !isfinite(origin_x) || !isfinite(origin_y)) {
        errno = EINVAL;
        return NULL;
    }

    if (rows > SIZE_MAX / columns) {
        errno = EOVERFLOW;
        return NULL;
    }

    count = rows * columns;

    if (count > (SIZE_MAX - sizeof(*grid)) / sizeof(grid->hexagons[0])) {
        errno = EOVERFLOW;
        return NULL;
    }

    allocation_size = sizeof(*grid) + count * sizeof(grid->hexagons[0]);
    grid = malloc(allocation_size);

    if (grid == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    grid->rows = rows;
    grid->columns = columns;
    grid->count = count;

    for (size_t row = 0; row < rows; ++row) {
        for (size_t column = 0; column < columns; ++column) {
            const size_t index = row * columns + column;
            const double row_offset = (row % 2U == 0U) ? 0.0 : 0.5;
            const double center_x =
                origin_x + sqrt_three * radius *
                               ((double)column + row_offset);
            const double center_y =
                origin_y + 1.5 * radius * (double)row;
            const double half_width = sqrt_three * radius * 0.5;
            Hexagon *hexagon = &grid->hexagons[index];

            if (!isfinite(center_x) || !isfinite(center_y) ||
                !isfinite(half_width)) {
                free(grid);
                errno = ERANGE;
                return NULL;
            }

            hexagon->points[0] =
                (Point){center_x + half_width, center_y - radius * 0.5};
            hexagon->points[1] =
                (Point){center_x + half_width, center_y + radius * 0.5};
            hexagon->points[2] = (Point){center_x, center_y + radius};
            hexagon->points[3] =
                (Point){center_x - half_width, center_y + radius * 0.5};
            hexagon->points[4] =
                (Point){center_x - half_width, center_y - radius * 0.5};
            hexagon->points[5] = (Point){center_x, center_y - radius};

            for (size_t point = 0; point < 6; ++point) {
                if (!isfinite(hexagon->points[point].x) ||
                    !isfinite(hexagon->points[point].y)) {
                    free(grid);
                    errno = ERANGE;
                    return NULL;
                }
            }
        }
    }

    return grid;
}

bool print_hexagon_grid(const HexagonGrid *grid)
{
    if (grid == NULL) {
        errno = EINVAL;
        return false;
    }

    if (printf("[") < 0) {
        return false;
    }

    for (size_t index = 0; index < grid->count; ++index) {
        if (index > 0 && printf(", ") < 0) {
            return false;
        }

        if (printf("[") < 0) {
            return false;
        }

        for (size_t point = 0; point < 6; ++point) {
            if (point > 0 && printf(", ") < 0) {
                return false;
            }

            if (printf("(%.6f, %.6f)",
                       grid->hexagons[index].points[point].x,
                       grid->hexagons[index].points[point].y) < 0) {
                return false;
            }
        }

        if (printf("]") < 0) {
            return false;
        }
    }

    if (printf("]\n") < 0 || fflush(stdout) == EOF) {
        return false;
    }

    return true;
}

int main(void)
{
    HexagonGrid *grid =
        calculate_hexagon_grid(3, 4, 10.0, 0.0, 0.0);

    if (grid == NULL) {
        perror("calculate_hexagon_grid");
        return EXIT_FAILURE;
    }

    if (!print_hexagon_grid(grid)) {
        free(grid);
        perror("print_hexagon_grid");
        return EXIT_FAILURE;
    }

    free(grid);
    return EXIT_SUCCESS;
}