#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[6];
} Hexagon;

Hexagon** create_hex_grid(int rows, int cols, double size, double start_x, double start_y) {
    if (rows <= 0 || cols <= 0 || size <= 0.0) {
        return NULL;
    }

    Hexagon** grid = (Hexagon**)malloc(rows * sizeof(Hexagon*));
    if (!grid) {
        return NULL;
    }

    for (int i = 0; i < rows; ++i) {
        grid[i] = (Hexagon*)malloc(cols * sizeof(Hexagon));
        if (!grid[i]) {
            for (int j = 0; j < i; ++j) {
                free(grid[j]);
            }
            free(grid);
            return NULL;
        }
    }

    double pi = acos(-1.0);
    double horiz_dist = sqrt(3.0) * size;
    double vert_dist = 1.5 * size;
    double offset = sqrt(3.0) / 2.0 * size;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            double cx = start_x + c * horiz_dist;
            if (r % 2 != 0) {
                cx += offset;
            }
            double cy = start_y + r * vert_dist;

            for (int k = 0; k < 6; ++k) {
                double angle_rad = (60.0 * k - 30.0) * pi / 180.0;
                grid[r][c].vertices[k].x = cx + size * cos(angle_rad);
                grid[r][c].vertices[k].y = cy + size * sin(angle_rad);
            }
        }
    }

    return grid;
}

void free_hex_grid(Hexagon** grid, int rows) {
    if (!grid) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        free(grid[i]);
    }
    free(grid);
}

int main(void) {
    int rows = 3;
    int cols = 4;
    double size = 10.0;
    double start_x = 0.0;
    double start_y = 0.0;

    Hexagon** grid = create_hex_grid(rows, cols, size, start_x, start_y);
    if (!grid) {
        return EXIT_FAILURE;
    }

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            printf("Hexagon [%d][%d]: ", r, c);
            for (int k = 0; k < 6; ++k) {
                printf("(%.2f, %.2f) ", grid[r][c].vertices[k].x, grid[r][c].vertices[k].y);
            }
            printf("\n");
        }
    }

    free_hex_grid(grid, rows);

    return EXIT_SUCCESS;
}