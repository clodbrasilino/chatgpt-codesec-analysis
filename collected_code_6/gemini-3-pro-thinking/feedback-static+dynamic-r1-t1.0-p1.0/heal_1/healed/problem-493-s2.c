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
    Hexagon *hexagons;
    size_t count;
} HexGrid;

HexGrid generate_hex_grid(size_t rows, size_t cols, double radius, double offset_x, double offset_y);

HexGrid generate_hex_grid(size_t rows, size_t cols, double radius, double offset_x, double offset_y) {
    HexGrid grid = {NULL, 0};

    if (rows == 0 || cols == 0 || radius <= 0.0) {
        return grid;
    }

    size_t total_hexagons = rows * cols;
    grid.hexagons = (Hexagon *)malloc(total_hexagons * sizeof(Hexagon));
    
    if (!grid.hexagons) {
        return grid;
    }

    grid.count = total_hexagons;

    double width = sqrt(3.0) * radius;
    double height = 2.0 * radius;

    size_t index = 0;
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            double cx = offset_x + (double)col * width;
            if (row % 2 == 1) {
                cx += width / 2.0;
            }
            double cy = offset_y + (double)row * (height * 0.75);

            for (int i = 0; i < 6; ++i) {
                double angle_deg = 60.0 * i - 30.0;
                double angle_rad = (M_PI / 180.0) * angle_deg;
                
                grid.hexagons[index].points[i].x = cx + radius * cos(angle_rad);
                grid.hexagons[index].points[i].y = cy + radius * sin(angle_rad);
            }
            index++;
        }
    }

    return grid;
}

int main(void) {
    size_t rows = 4;
    size_t cols = 3;
    double radius = 10.0;

    HexGrid grid = generate_hex_grid(rows, cols, radius, 0.0, 0.0);

    if (!grid.hexagons) {
        fprintf(stderr, "Failed to allocate memory for hexagon grid.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < grid.count; ++i) {
        printf("Hexagon %zu:\n", i);
        for (int j = 0; j < 6; ++j) {
            printf("  Point %d: (%f, %f)\n", j, grid.hexagons[i].points[j].x, grid.hexagons[i].points[j].y);
        }
    }

    free(grid.hexagons);

    return EXIT_SUCCESS;
}