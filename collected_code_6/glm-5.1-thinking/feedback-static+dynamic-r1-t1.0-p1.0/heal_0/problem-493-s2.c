#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[6];
} Hexagon;

Hexagon** create_hex_grid(int rows, int cols, double size, double origin_x, double origin_y) {
    if (rows <= 0 || cols <= 0 || size <= 0.0) {
        return NULL;
    }

    Hexagon **grid = malloc(rows * sizeof(*grid));
    if (!grid) {
        return NULL;
    }

    for (int i = 0; i < rows; i++) {
        grid[i] = malloc(cols * sizeof(**grid));
        if (!grid[i]) {
            for (int j = 0; j < i; j++) {
                free(grid[j]);
            }
            free(grid);
            return NULL;
        }
    }

    double horiz_dist = size * sqrt(3.0);
    double vert_dist = size * 1.5;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            double cx = origin_x + c * horiz_dist;
            if (r % 2 != 0) {
                cx += horiz_dist / 2.0;
            }
            double cy = origin_y + r * vert_dist;

            for (int v = 0; v < 6; v++) {
                double angle = (PI / 180.0) * (60.0 * v - 30.0);
                grid[r][c].vertices[v].x = cx + size * cos(angle);
                grid[r][c].vertices[v].y = cy + size * sin(angle);
            }
        }
    }

    return grid;
}

void free_hex_grid(Hexagon **grid, int rows) {
    if (!grid) {
        return;
    }
    for (int i = 0; i < rows; i++) {
        free(grid[i]);
    }
    free(grid);
}

int main(void) {
    int rows = 3;
    int cols = 4;
    double size = 10.0;
    
    Hexagon **grid = create_hex_grid(rows, cols, size, 0.0, 0.0);
    if (!grid) {
        return EXIT_FAILURE;
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            printf("Hexagon [%d][%d]: ", r, c);
            for (int v = 0; v < 6; v++) {
                printf("(%.2f, %.2f) ", grid[r][c].vertices[v].x, grid[r][c].vertices[v].y);
            }
            printf("\n");
        }
    }

    free_hex_grid(grid, rows);
    
    return EXIT_SUCCESS;
}