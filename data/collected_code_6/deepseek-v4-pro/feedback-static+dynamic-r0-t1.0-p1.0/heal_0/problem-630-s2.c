#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

Coordinate* get_adjacent_coordinates(Coordinate coord, int *count) {
    Coordinate *adjacent = (Coordinate*)malloc(8 * sizeof(Coordinate));
    if (adjacent == NULL) {
        *count = 0;
        return NULL;
    }
    
    int i = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) continue;
            adjacent[i].x = coord.x + dx;
            adjacent[i].y = coord.y + dy;
            i++;
        }
    }
    
    *count = 8;
    return adjacent;
}

int main(void) {
    Coordinate coord = {5, 7};
    int count = 0;
    
    Coordinate *adjacent = get_adjacent_coordinates(coord, &count);
    
    if (adjacent == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Adjacent coordinates of (%d,%d):\n", coord.x, coord.y);
    for (int i = 0; i < count; i++) {
        printf("(%d,%d)\n", adjacent[i].x, adjacent[i].y);
    }
    
    free(adjacent);
    return 0;
}