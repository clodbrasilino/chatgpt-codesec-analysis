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
    Hexagon **cells;
    int rows;
    int cols;
} HexGrid;

HexGrid* calculate_hex_grid(int rows, int cols, double radius);
void free_hex_grid(HexGrid *grid);

HexGrid* calculate_hex_grid(int rows, int cols, double radius) {
    if (rows <= 0 || cols <= 0 || radius <= 0) {
        return NULL;
    }

    HexGrid *grid = malloc(sizeof(HexGrid));
    if (grid == NULL) {
        return NULL;
    }

    grid->rows = rows;
    grid->cols = cols;

    grid->cells = malloc((size_t)rows * sizeof(Hexagon*));
    if (grid->cells == NULL) {
        free(grid);
        return NULL;
    }

    for (int r = 0; r < rows; ++r) {
        grid->cells[r] = malloc((size_t)cols * sizeof(Hexagon));
        if (grid->cells[r] == NULL) {
            for (int i = 0; i < r; ++i) {
                free(grid->cells[i]);
            }
            free(grid->cells);
            free(grid);
            return NULL;
        }
    }

    double horizontal_spacing = sqrt(3.0) * radius;
    double vertical_spacing = 1.5 * radius;

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            double center_x = (double)c * horizontal_spacing;
            if (r % 2 == 1) {
                center_x += horizontal_spacing / 2.0;
            }
            double center_y = (double)r * vertical_spacing;

            for (int v = 0; v < 6; ++v) {
                double angle = (PI / 3.0) * (double)v + (PI / 6.0);
                grid->cells[r][c].vertices[v].x = center_x + radius * cos(angle);
                grid->cells[r][c].vertices[v].y = center_y + radius * sin(angle);
            }
        }
    }

    return grid;
}

void free_hex_grid(HexGrid *grid) {
    if (grid == NULL) {
        return;
    }

    if (grid->cells != NULL) {
        for (int r = 0; r < grid->rows; ++r) {
            free(grid->cells[r]);
        }
        free(grid->cells);
    }

    free(grid);
}

int main(void) {
    int rows = 3;
    int cols = 4;
    double radius = 1.0;

    HexGrid *grid = calculate_hex_grid(rows, cols, radius);
    if (grid == NULL) {
        fprintf(stderr, "Error: Failed to allocate hex grid.\n");
        return 1;
    }

    for (int r = 0; r < grid->rows; ++r) {
        for (int c = 0; c < grid->cols; ++c) {
            printf("Hexagon[%d][%d]: ", r, c);
            for (int v = 0; v < 6; ++v) {
                printf("(%.3f, %.3f)%s",
                       grid->cells[r][c].vertices[v].x,
                       grid->cells[r][c].vertices[v].y,
                       (v == 5) ? "\n" : " ");
            }
        }
    }

    free_hex_grid(grid);
    return 0;
}