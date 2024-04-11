#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

Hexagon* calculate_hexagon_grid(int grid_size, double hexagon_size) {
    Hexagon* grid = malloc(grid_size * sizeof(Hexagon));
    double half_hexagon_size = hexagon_size / 2.0;
    double row_height = 1.5 * hexagon_size;
    double col_width = 2.0 * hexagon_size;

    for (int i = 0; i < grid_size; i++) {
        for (int j = 0; j < 6; j++) {
            double angle_deg = 60 * j - 30;
            double angle_rad = M_PI / 180 * angle_deg;
            grid[i].points[j].x = i * col_width + hexagon_size * cos(angle_rad);
            grid[i].points[j].y = i * row_height + hexagon_size * sin(angle_rad);
        }
    }

    return grid;
}

void print_hexagon_grid(Hexagon* grid, int grid_size) {
    for (int i = 0; i < grid_size; i++) {
        printf("Hexagon %d:\n", i + 1);
        for (int j = 0; j < 6; j++) {
            printf("Point %d: (%f, %f)\n", j + 1, grid[i].points[j].x, grid[i].points[j].y);
        }
    }
}

int main() {
    int grid_size = 5;
    double hexagon_size = 1.0;
    Hexagon* grid = calculate_hexagon_grid(grid_size, hexagon_size);
    print_hexagon_grid(grid, grid_size);
    free(grid);
    return 0;
}