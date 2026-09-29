#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#define HEX_SIDES 6
#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
} Point;

typedef Point Hexagon[HEX_SIDES];

Hexagon *create_hexagon_grid(int rows, int cols, double radius, size_t *out_count);

Hexagon *create_hexagon_grid(int rows, int cols, double radius, size_t *out_count)
{
    Hexagon *grid;
    size_t total;
    size_t r;
    size_t c;
    size_t index;
    int i;
    double sqrt3;

    if (out_count == NULL) {
        return NULL;
    }
    *out_count = 0;

    if (rows <= 0 || cols <= 0) {
        return NULL;
    }
    if (!isfinite(radius) || radius <= 0.0) {
        return NULL;
    }
    if ((size_t)rows > SIZE_MAX / (size_t)cols) {
        return NULL;
    }
    total = (size_t)rows * (size_t)cols;
    if (total > SIZE_MAX / sizeof(*grid)) {
        return NULL;
    }

    grid = malloc(total * sizeof(*grid));
    if (grid == NULL) {
        return NULL;
    }

    sqrt3 = sqrt(3.0);

    for (r = 0; r < (size_t)rows; ++r) {
        for (c = 0; c < (size_t)cols; ++c) {
            double cx = radius * sqrt3 * ((double)c + 0.5 * (double)(r % 2u));
            double cy = radius * 1.5 * (double)r;
            index = r * (size_t)cols + c;
            for (i = 0; i < HEX_SIDES; ++i) {
                double angle = (PI / 180.0) * (60.0 * (double)i - 30.0);
                grid[index][i].x = cx + radius * cos(angle);
                grid[index][i].y = cy + radius * sin(angle);
            }
        }
    }

    *out_count = total;
    return grid;
}

int main(void)
{
    int rows = 3;
    int cols = 4;
    double radius = 10.0;
    size_t count = 0;
    size_t h;
    int v;
    Hexagon *grid;

    grid = create_hexagon_grid(rows, cols, radius, &count);
    if (grid == NULL) {
        fprintf(stderr, "Error: failed to create hexagon grid\n");
        return EXIT_FAILURE;
    }

    for (h = 0; h < count; ++h) {
        printf("Hexagon %zu:\n", h);
        for (v = 0; v < HEX_SIDES; ++v) {
            printf("  vertex %d: (%8.3f, %8.3f)\n", v, grid[h][v].x, grid[h][v].y);
        }
    }

    free(grid);
    grid = NULL;

    return EXIT_SUCCESS;
}