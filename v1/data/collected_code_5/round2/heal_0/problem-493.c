#include <stdio.h>
#include<stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef Point* Hexagon[6];

Hexagon* hexagonalGrid(int width, int height, double scale) {
    Hexagon* grid = (Hexagon*) malloc(sizeof(Hexagon) * width * height);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Hexagon *hex = &grid[i * width + j];
            for (int k = 0; k < 6; ++k) {
                (*hex)[k] = (Point*) malloc(sizeof(Point));
                (*hex)[k]->x = (j + 0.5 * (i % 2) + k%3 - 1) * scale;
                (*hex)[k]->y = (i + 0.5 * (k / 3) - 0.5) * scale;
            }
        }
    }
    return grid;
}

void cleanup(Hexagon* grid, int width, int height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Hexagon* hex = &grid[i * width + j];
            for (int k = 0; k < 6; ++k) {
                free((*hex)[k]);
            }
        }
    }
    free(grid);
}

int main() {
    int width = 10;
    int height = 10;
    double scale = 1.0;
    Hexagon* grid = hexagonalGrid(width, height, scale);
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            Hexagon* hex = &grid[i * width + j];
            for (int k = 0; k < 6; ++k) {
                printf("(%f, %f) ", (*hex)[k]->x, (*hex)[k]->y);
            }
            printf("\n");
        }
    }

    cleanup(grid, width, height);

    return 0;
}