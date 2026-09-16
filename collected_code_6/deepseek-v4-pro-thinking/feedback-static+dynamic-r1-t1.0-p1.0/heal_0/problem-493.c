#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

void free_hex_grid(Point ***grid, int rows, int cols) {
    if (grid == NULL) {
        return;
    }
    for (int r = 0; r < rows; r++) {
        if (grid[r] == NULL) {
            continue;
        }
        for (int c = 0; c < cols; c++) {
            free(grid[r][c]);
        }
        free(grid[r]);
    }
    free(grid);
}

Point ***calculate_hex_grid(int rows, int cols, double radius) {
    if (rows <= 0 || cols <= 0 || radius <= 0.0) {
        return NULL;
    }

    const double PI = acos(-1.0);
    const double SQRT3 = sqrt(3.0);

    Point ***grid = malloc((size_t)rows * sizeof(Point **));
    if (grid == NULL) {
        return NULL;
    }

    for (int r = 0; r < rows; r++) {
        grid[r] = NULL;
    }

    for (int r = 0; r < rows; r++) {
        grid[r] = malloc((size_t)cols * sizeof(Point *));
        if (grid[r] == NULL) {
            free_hex_grid(grid, rows, cols);
            return NULL;
        }

        for (int c = 0; c < cols; c++) {
            grid[r][c] = NULL;
        }

        for (int c = 0; c < cols; c++) {
            grid[r][c] = malloc(6 * sizeof(Point));
            if (grid[r][c] == NULL) {
                free_hex_grid(grid, rows, cols);
                return NULL;
            }
        }
    }

    for (int r = 0; r < rows; r++) {
        double center_y = 1.5 * radius * (double)r;
        double row_offset = (r % 2 == 1) ? (SQRT3 * radius / 2.0) : 0.0;

        for (int c = 0; c < cols; c++) {
            double center_x = SQRT3 * radius * (double)c + row_offset;

            for (int v = 0; v < 6; v++) {
                double angle = (double)v * PI / 3.0 + PI / 6.0;
                grid[r][c][v].x = center_x + radius * cos(angle);
                grid[r][c][v].y = center_y + radius * sin(angle);
            }
        }
    }

    return grid;
}

int main(void) {
    int rows = 3;
    int cols = 4;
    double radius = 10.0;

    Point ***grid = calculate_hex_grid(rows, cols, radius);
    if (grid == NULL) {
        return 1;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            for (int v = 0; v < 6; v++) {
                printf("(%f, %f) ", grid[r][c][v].x, grid[r][c][v].y);
            }
            printf("\n");
        }
    }

    free_hex_grid(grid, rows, cols);
    return 0;
}