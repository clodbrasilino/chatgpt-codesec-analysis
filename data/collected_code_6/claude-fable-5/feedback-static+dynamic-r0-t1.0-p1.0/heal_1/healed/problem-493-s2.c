#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
} HexGrid;

static int compute_hexagon(double center_x, double center_y, double radius, Hexagon *hex)
{
    size_t i;

    if (hex == NULL || radius <= 0.0) {
        return -1;
    }

    for (i = 0U; i < 6U; i++) {
        const double angle = (M_PI / 3.0) * (double)i;
        hex->vertices[i].x = center_x + (radius * cos(angle));
        hex->vertices[i].y = center_y + (radius * sin(angle));
    }

    return 0;
}

HexGrid *calculate_hex_grid(size_t rows, size_t cols, double radius)
{
    HexGrid *grid;
    size_t row;
    size_t col;
    size_t index;
    double horiz_spacing;
    double vert_spacing;
    double center_x;
    double center_y;

    if (rows == 0U || cols == 0U || radius <= 0.0) {
        return NULL;
    }

    if (cols > SIZE_MAX / rows) {
        return NULL;
    }

    grid = malloc(sizeof(HexGrid));
    if (grid == NULL) {
        return NULL;
    }

    grid->count = rows * cols;

    if (grid->count > SIZE_MAX / sizeof(Hexagon)) {
        free(grid);
        return NULL;
    }

    grid->hexagons = malloc(grid->count * sizeof(Hexagon));
    if (grid->hexagons == NULL) {
        free(grid);
        return NULL;
    }

    horiz_spacing = radius * 1.5;
    vert_spacing = radius * sqrt(3.0);

    for (row = 0U; row < rows; row++) {
        for (col = 0U; col < cols; col++) {
            index = (row * cols) + col;
            center_x = (double)col * horiz_spacing;
            center_y = (double)row * vert_spacing;
            if ((col % 2U) == 1U) {
                center_y += vert_spacing / 2.0;
            }
            if (compute_hexagon(center_x, center_y, radius, &grid->hexagons[index]) != 0) {
                free(grid->hexagons);
                free(grid);
                return NULL;
            }
        }
    }

    return grid;
}

void free_hex_grid(HexGrid *grid)
{
    if (grid != NULL) {
        free(grid->hexagons);
        free(grid);
    }
}

int main(void)
{
    HexGrid *grid;
    size_t i;
    size_t j;

    grid = calculate_hex_grid(3U, 4U, 1.0);
    if (grid == NULL) {
        fprintf(stderr, "Failed to create hexagon grid\n");
        return EXIT_FAILURE;
    }

    for (i = 0U; i < grid->count; i++) {
        if (printf("Hexagon %zu:\n", i) < 0) {
            free_hex_grid(grid);
            return EXIT_FAILURE;
        }
        for (j = 0U; j < 6U; j++) {
            if (printf("  (%.4f, %.4f)\n",
                       grid->hexagons[i].vertices[j].x,
                       grid->hexagons[i].vertices[j].y) < 0) {
                free_hex_grid(grid);
                return EXIT_FAILURE;
            }
        }
    }

    free_hex_grid(grid);
    return EXIT_SUCCESS;
}