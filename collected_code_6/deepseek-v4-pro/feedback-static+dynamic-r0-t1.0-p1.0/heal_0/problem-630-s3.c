#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coord;

Coord* get_adjacent_coords(Coord coord, int* count) {
    static const int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    static const int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    
    Coord* adjacent = (Coord*)malloc(8 * sizeof(Coord));
    if (adjacent == NULL) {
        *count = 0;
        return NULL;
    }
    
    for (int i = 0; i < 8; i++) {
        adjacent[i].x = coord.x + dx[i];
        adjacent[i].y = coord.y + dy[i];
    }
    
    *count = 8;
    return adjacent;
}

int main(void) {
    Coord point = {5, 5};
    int count = 0;
    
    Coord* neighbors = get_adjacent_coords(point, &count);
    if (neighbors == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }
    
    printf("Adjacent coordinates of (%d, %d):\n", point.x, point.y);
    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", neighbors[i].x, neighbors[i].y);
    }
    
    free(neighbors);
    return 0;
}