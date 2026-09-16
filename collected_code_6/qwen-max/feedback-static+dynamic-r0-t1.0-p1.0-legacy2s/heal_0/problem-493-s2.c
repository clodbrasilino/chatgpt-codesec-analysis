#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

Hexagon* create_hexagon(int i, int j) {
    Hexagon *h = (Hexagon*)malloc(sizeof(Hexagon));
    if (h == NULL) return NULL;
    h->points[0] = (Point){2 * i, 2 * j};
    h->points[1] = (Point){2 * i + 1, 2 * j + 1};
    h->points[2] = (Point){2 * i, 2 * j + 2};
    h->points[3] = (Point){2 * i - 1, 2 * j + 1};
    h->points[4] = (Point){2 * i - 2, 2 * j};
    h->points[5] = (Point){2 * i - 1, 2 * j - 1};
    return h;
}

Hexagon** calculate_hexagon_grid(int rows, int cols) {
    Hexagon **grid = (Hexagon**)malloc(rows * sizeof(Hexagon*));
    if (grid == NULL) return NULL;
    for (int i = 0; i < rows; ++i) {
        grid[i] = (Hexagon*)malloc(cols * sizeof(Hexagon));
        if (grid[i] == NULL) {
            for (int k = 0; k < i; ++k) free(grid[k]);
            free(grid);
            return NULL;
        }
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = *create_hexagon(i, j);
        }
    }
    return grid;
}

void print_hexagon_grid(Hexagon **grid, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            for (int k = 0; k < 6; ++k) {
                printf("(%d, %d) ", grid[i][j].points[k].x, grid[i][j].points[k].y);
            }
            printf("\n");
        }
    }
}

void free_hexagon_grid(Hexagon **grid, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(grid[i]);
    }
    free(grid);
}

int main() {
    int rows = 2;
    int cols = 3;
    Hexagon **hexagon_grid = calculate_hexagon_grid(rows, cols);
    if (hexagon_grid != NULL) {
        print_hexagon_grid(hexagon_grid, rows, cols);
        free_hexagon_grid(hexagon_grid, rows);
    }
    return 0;
}