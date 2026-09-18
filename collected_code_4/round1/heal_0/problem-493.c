#include <stdio.h>
#include <stdlib.h>

// The structure to hold coordinates
typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

// Function prototype is required
Hexagon* calculate_hexagon_grid(int grid_size);

int main(){
    int grid_size = 5; // choose your grid size
    Hexagon *hexagonGrid = calculate_hexagon_grid(grid_size);
    if(hexagonGrid == NULL)
        return -1;
    for(int i = 0; i < grid_size; ++i){
        for(int j = 0; j < 6; ++j){
            printf("Hexagon: %d, Point: %d, X: %f, Y: %f\n",
                   i, j, hexagonGrid[i].points[j].x, hexagonGrid[i].points[j].y);
        }
    }
    free(hexagonGrid);
    return 0;
}

// Hexagon grid generation function
Hexagon* calculate_hexagon_grid(int grid_size){
    Hexagon *hexagonGrid;
    hexagonGrid = malloc(sizeof(Hexagon) * grid_size);
    if(hexagonGrid == NULL)
        return NULL;

    for(int i = 0; i < grid_size; ++i){
        for(int j = 0; j < 6; ++j){
            hexagonGrid[i].points[j].x = j + (i * 0.5);
            hexagonGrid[i].points[j].y = j + (i * 0.5);
        }
    }
    return hexagonGrid;
}