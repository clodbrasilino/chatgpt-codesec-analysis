#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point points[6];
} Hexagon;

Hexagon* calculateHexagonGrid(int size) {
    Hexagon* grid = malloc(size * sizeof(Hexagon));
    int index = 0;
    
    for (int row = 0; row < size; row++) {
        for (int col = 0; col < size; col++) {
            int x = col * 2 + row % 2;
            int y = row * 2;
            
            grid[index].points[0].x = x;
            grid[index].points[0].y = y + 1;
            grid[index].points[1].x = x + 1;
            grid[index].points[1].y = y;
            grid[index].points[2].x = x + 2;
            grid[index].points[2].y = y + 1;
            grid[index].points[3].x = x + 2;
            grid[index].points[3].y = y + 3;
            grid[index].points[4].x = x + 1;
            grid[index].points[4].y = y + 4;
            grid[index].points[5].x = x;
            grid[index].points[5].y = y + 3;
            
            index++;
        }
    }
    
    return grid;
}

int main() {
    int size = 3;
    Hexagon* grid = calculateHexagonGrid(size);
    
    for (int i = 0; i < size*size; i++) {
        for (int j = 0; j < 6; j++) {
            printf("(%d,%d) ", grid[i].points[j].x, grid[i].points[j].y);
        }
        printf("\n");
    }
    
    free(grid);
    
    return 0;
}