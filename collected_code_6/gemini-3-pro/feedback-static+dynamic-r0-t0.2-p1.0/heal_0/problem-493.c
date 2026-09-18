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

typedef struct {
    Hexagon* hexagons;
    size_t count;
} HexagonGrid;

HexagonGrid calculate_hexagon_grid(int rows, int cols, double size, double start_x, double start_y) {
    HexagonGrid grid = {NULL, 0};
    
    if (rows <= 0 || cols <= 0 || size <= 0.0) {
        return grid;
    }

    size_t total_hexagons = (size_t)rows * (size_t)cols;
    grid.hexagons = (Hexagon*)malloc(total_hexagons * sizeof(Hexagon));
    
    if (!grid.hexagons) {
        return grid;
    }

    grid.count = total_hexagons;
    double width = sqrt(3.0) * size;
    double height = 2.0 * size;
    double horiz_spacing = width;
    double vert_spacing = 3.0 / 4.0 * height;

    size_t index = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            double center_x = start_x + c * horiz_spacing;
            double center_y = start_y + r * vert_spacing;

            if (r % 2 != 0) {
                center_x += width / 2.0;
            }

            for (int i = 0; i < 6; i++) {
                double angle_deg = 60.0 * i - 30.0;
                double angle_rad = M_PI / 180.0 * angle_deg;
                grid.hexagons[index].points[i].x = center_x + size * cos(angle_rad);
                grid.hexagons[index].points[i].y = center_y + size * sin(angle_rad);
            }
            index++;
        }
    }

    return grid;
}

void free_hexagon_grid(HexagonGrid* grid) {
    if (grid && grid->hexagons) {
        free(grid->hexagons);
        grid->hexagons = NULL;
        grid->count = 0;
    }
}

int main(void) {
    int rows = 3;
    int cols = 3;
    double size = 10.0;
    double start_x = 0.0;
    double start_y = 0.0;

    HexagonGrid grid = calculate_hexagon_grid(rows, cols, size, start_x, start_y);

    if (!grid.hexagons) {
        fprintf(stderr, "Failed to allocate memory for hexagon grid.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < grid.count; i++) {
        printf("Hexagon %zu:\n", i);
        for (int j = 0; j < 6; j++) {
            printf("  Point %d: (%.2f, %.2f)\n", j, grid.hexagons[i].points[j].x, grid.hexagons[i].points[j].y);
        }
    }

    free_hexagon_grid(&grid);

    return EXIT_SUCCESS;
}