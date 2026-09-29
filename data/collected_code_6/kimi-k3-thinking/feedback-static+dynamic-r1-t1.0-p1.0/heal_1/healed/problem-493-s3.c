#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define HEX_PI 3.14159265358979323846
#define HEX_VERTEX_COUNT 6

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[HEX_VERTEX_COUNT];
} Hexagon;

static void compute_hexagon_vertices(Hexagon *hexagon, double center_x, double center_y, double size)
{
    int i;

    if (hexagon == NULL) {
        return;
    }

    for (i = 0; i < HEX_VERTEX_COUNT; i++) {
        const double angle = (HEX_PI / 3.0) * (double)i;
        hexagon->vertices[i].x = center_x + size * cos(angle);
        hexagon->vertices[i].y = center_y + size * sin(angle);
    }
}

Hexagon **create_hexagon_grid(size_t rows, size_t cols, double size, double origin_x, double origin_y)
{
    Hexagon **grid;
    size_t r;
    size_t c;
    double horizontal_spacing;
    double vertical_spacing;
    double center_x;
    double center_y;

    if (rows == 0U || cols == 0U || size <= 0.0) {
        return NULL;
    }

    if (rows > SIZE_MAX / sizeof(Hexagon *) || cols > SIZE_MAX / sizeof(Hexagon)) {
        return NULL;
    }

    grid = malloc(rows * sizeof(*grid));
    if (grid == NULL) {
        return NULL;
    }

    horizontal_spacing = 1.5 * size;
    vertical_spacing = sqrt(3.0) * size;

    for (r = 0U; r < rows; r++) {
        grid[r] = malloc(cols * sizeof(*grid[r]));
        if (grid[r] == NULL) {
            while (r > 0U) {
                r--;
                free(grid[r]);
            }
            free(grid);
            return NULL;
        }

        for (c = 0U; c < cols; c++) {
            center_x = origin_x + (double)c * horizontal_spacing;
            center_y = origin_y + (double)r * vertical_spacing;
            if ((c % 2U) == 1U) {
                center_y += vertical_spacing / 2.0;
            }
            compute_hexagon_vertices(&grid[r][c], center_x, center_y, size);
        }
    }

    return grid;
}

void free_hexagon_grid(Hexagon **grid, size_t rows)
{
    size_t r;

    if (grid == NULL) {
        return;
    }

    for (r = 0U; r < rows; r++) {
        free(grid[r]);
    }

    free(grid);
}

int main(void)
{
    const size_t rows = 3U;
    const size_t cols = 4U;
    const double size = 10.0;
    Hexagon **grid;
    size_t r;
    size_t c;
    int v;
    int status;

    status = EXIT_SUCCESS;

    grid = create_hexagon_grid(rows, cols, size, 0.0, 0.0);
    if (grid == NULL) {
        (void)fprintf(stderr, "Error: unable to create hexagon grid.\n");
        return EXIT_FAILURE;
    }

    for (r = 0U; r < rows; r++) {
        for (c = 0U; c < cols; c++) {
            (void)printf("Hexagon [%zu][%zu]:", r, c);
            for (v = 0; v < HEX_VERTEX_COUNT; v++) {
                (void)printf(" (%.2f, %.2f)", grid[r][c].vertices[v].x, grid[r][c].vertices[v].y);
            }
            (void)printf("\n");
        }
    }

    if (fflush(stdout) == EOF || ferror(stdout)) {
        status = EXIT_FAILURE;
    }

    free_hexagon_grid(grid, rows);

    return status;
}