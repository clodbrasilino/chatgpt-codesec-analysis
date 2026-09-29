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

typedef struct {
    Hexagon *hexagons;
    size_t count;
} HexagonGrid;

HexagonGrid generate_hexagon_grid(size_t rows, size_t cols, double size, double start_x, double start_y) {
    HexagonGrid grid = {NULL, 0};

    if (rows == 0 || cols == 0 || size <= 0.0) {
        return grid;
    }

    size_t total_hexagons = rows * cols;
    grid.hexagons = (Hexagon *)malloc(total_hexagons * sizeof(Hexagon));
    if (!grid.hexagons) {
        return grid;
    }

    grid.count = total_hexagons;

    double width = sqrt(3.0) * size;
    double height = 2.0 * size;

    size_t index = 0;
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            double cx = start_x + ((double)col * width);
            if (row % 2 != 0) {
                cx += (width / 2.0);
            }
            double cy = start_y + ((double)row * height * 0.75);

            for (int i = 0; i < 6; ++i) {
                double angle_deg = 60.0 * (double)i - 30.0;
                double angle_rad = (PI / 180.0) * angle_deg;
                grid.hexagons[index].vertices[i].x = cx + size * cos(angle_rad);
                grid.hexagons[index].vertices[i].y = cy + size * sin(angle_rad);
            }
            index++;
        }
    }

    return grid;
}

void free_hexagon_grid(HexagonGrid *grid) {
    if (grid != NULL && grid->hexagons != NULL) {
        free(grid->hexagons);
        grid->hexagons = NULL;
        grid->count = 0;
    }
}

int main(void) {
    size_t rows = 4;
    size_t cols = 3;
    double size = 10.0;
    double start_x = 0.0;
    double start_y = 0.0;

    HexagonGrid grid = generate_hexagon_grid(rows, cols, size, start_x, start_y);

    if (grid.hexagons == NULL || grid.count == 0) {
        fprintf(stderr, "Error: Failed to generate hexagon grid.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < grid.count; ++i) {
        printf("Hexagon %zu:\n", i);
        for (int j = 0; j < 6; ++j) {
            printf("  (%.4f, %.4f)\n", grid.hexagons[i].vertices[j].x, grid.hexagons[i].vertices[j].y);
        }
    }

    free_hexagon_grid(&grid);

    return EXIT_SUCCESS;
}