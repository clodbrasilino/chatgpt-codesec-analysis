#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

Hexagon** calculate_hexagon_grid(int rows, int cols, double size, double start_x, double start_y) {
    if (rows <= 0 || cols <= 0 || size <= 0.0) {
        return NULL;
    }

    Hexagon** grid = (Hexagon**)malloc((size_t)rows * sizeof(Hexagon*));
    if (!grid) {
        return NULL;
    }

    double width = sqrt(3.0) * size;
    double height = 2.0 * size;
    double horiz = width;
    double vert = 3.0 / 4.0 * height;

    for (int r = 0; r < rows; r++) {
        grid[r] = (Hexagon*)malloc((size_t)cols * sizeof(Hexagon));
        if (!grid[r]) {
            for (int i = 0; i < r; i++) {
                free(grid[i]);
            }
            free(grid);
            return NULL;
        }

        for (int c = 0; c < cols; c++) {
            double cx = start_x + (double)c * horiz;
            double cy = start_y + (double)r * vert;

            if (r % 2 != 0) {
                cx += horiz / 2.0;
            }

            for (int i = 0; i < 6; i++) {
                double angle_deg = 60.0 * i - 30.0;
                double angle_rad = M_PI / 180.0 * angle_deg;
                grid[r][c].points[i].x = cx + size * cos(angle_rad);
                grid[r][c].points[i].y = cy + size * sin(angle_rad);
            }
        }
    }

    return grid;
}

void free_hexagon_grid(Hexagon** grid, int rows) {
    if (!grid) {
        return;
    }
    for (int r = 0; r < rows; r++) {
        free(grid[r]);
    }
    free(grid);
}

int main(void) {
    int rows = 3;
    int cols = 3;
    double size = 10.0;
    double start_x = 0.0;
    double start_y = 0.0;

    Hexagon** grid = calculate_hexagon_grid(rows, cols, size, start_x, start_y);
    if (!grid) {
        fprintf(stderr, "Failed to allocate memory for hexagon grid.\n");
        return 1;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("Hexagon at row %d, col %d:\n", r, c);
            for (int i = 0; i < 6; i++) {
                printf("  Point %d: (%.2f, %.2f)\n", i, grid[r][c].points[i].x, grid[r][c].points[i].y);
            }
        }
    }

    free_hexagon_grid(grid, rows);

    return 0;
}