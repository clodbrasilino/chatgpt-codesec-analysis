#include <errno.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef Point Hexagon[6];

Hexagon *calculate_hexagon_grid(
    size_t rows,
    size_t columns,
    double side_length,
    double origin_x,
    double origin_y,
    size_t *hexagon_count
);

void free_hexagon_grid(Hexagon *grid);

int print_hexagon_grid(const Hexagon *grid, size_t hexagon_count);

Hexagon *calculate_hexagon_grid(
    size_t rows,
    size_t columns,
    double side_length,
    double origin_x,
    double origin_y,
    size_t *hexagon_count
) {
    Hexagon *grid;
    size_t total;
    double half_side;
    double half_width;
    double horizontal_spacing;
    double vertical_spacing;

    if (hexagon_count == NULL) {
        errno = EINVAL;
        return NULL;
    }

    *hexagon_count = 0;

    if (rows == 0 || columns == 0 || side_length <= 0.0 ||
        !isfinite(side_length) || !isfinite(origin_x) ||
        !isfinite(origin_y)) {
        errno = EINVAL;
        return NULL;
    }

    if (rows > SIZE_MAX / columns) {
        errno = EOVERFLOW;
        return NULL;
    }

    total = rows * columns;

    if (total > SIZE_MAX / sizeof(Hexagon)) {
        errno = EOVERFLOW;
        return NULL;
    }

    half_side = side_length / 2.0;
    half_width = sqrt(3.0) * half_side;
    horizontal_spacing = sqrt(3.0) * side_length;
    vertical_spacing = 1.5 * side_length;

    if (!isfinite(half_width) || !isfinite(horizontal_spacing) ||
        !isfinite(vertical_spacing)) {
        errno = ERANGE;
        return NULL;
    }

    grid = calloc(total, sizeof(*grid));
    if (grid == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    for (size_t row = 0; row < rows; ++row) {
        double row_offset = (row % 2U == 0U) ? 0.0 : 0.5;

        for (size_t column = 0; column < columns; ++column) {
            size_t index = row * columns + column;
            double center_x = origin_x +
                horizontal_spacing * ((double)column + row_offset);
            double center_y = origin_y +
                vertical_spacing * (double)row;
            Point vertices[6] = {
                {center_x, center_y - side_length},
                {center_x + half_width, center_y - half_side},
                {center_x + half_width, center_y + half_side},
                {center_x, center_y + side_length},
                {center_x - half_width, center_y + half_side},
                {center_x - half_width, center_y - half_side}
            };

            if (!isfinite(center_x) || !isfinite(center_y)) {
                free(grid);
                errno = ERANGE;
                return NULL;
            }

            for (size_t vertex = 0; vertex < 6; ++vertex) {
                if (!isfinite(vertices[vertex].x) ||
                    !isfinite(vertices[vertex].y)) {
                    free(grid);
                    errno = ERANGE;
                    return NULL;
                }

                grid[index][vertex] = vertices[vertex];
            }
        }
    }

    *hexagon_count = total;
    return grid;
}

void free_hexagon_grid(Hexagon *grid) {
    free(grid);
}

int print_hexagon_grid(const Hexagon *grid, size_t hexagon_count) {
    if (grid == NULL) {
        return -1;
    }

    if (fputs("[\n", stdout) == EOF) {
        return -1;
    }

    for (size_t hexagon = 0; hexagon < hexagon_count; ++hexagon) {
        if (fputs("  [", stdout) == EOF) {
            return -1;
        }

        for (size_t vertex = 0; vertex < 6; ++vertex) {
            if (printf(
                    "(%.6f, %.6f)%s",
                    grid[hexagon][vertex].x,
                    grid[hexagon][vertex].y,
                    vertex < 5 ? ", " : ""
                ) < 0) {
                return -1;
            }
        }

        if (fputs(hexagon + 1 < hexagon_count ? "],\n" : "]\n", stdout)
            == EOF) {
            return -1;
        }
    }

    if (fputs("]\n", stdout) == EOF) {
        return -1;
    }

    return 0;
}

int main(void) {
    Hexagon *grid;
    size_t hexagon_count;
    int print_result;

    grid = calculate_hexagon_grid(
        3,
        4,
        10.0,
        0.0,
        0.0,
        &hexagon_count
    );

    if (grid == NULL) {
        return EXIT_FAILURE;
    }

    print_result = print_hexagon_grid(grid, hexagon_count);
    free_hexagon_grid(grid);

    if (print_result != 0 || fflush(stdout) == EOF) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}