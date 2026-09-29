#include <stdio.h>

typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    Coordinate coordinates[8];
    int count;
} AdjacentCoordinates;

AdjacentCoordinates get_adjacent_coordinates(Coordinate c) {
    AdjacentCoordinates result;
    result.count = 8;
    result.coordinates[0].x = c.x - 1; result.coordinates[0].y = c.y - 1;
    result.coordinates[1].x = c.x - 1; result.coordinates[1].y = c.y;
    result.coordinates[2].x = c.x - 1; result.coordinates[2].y = c.y + 1;
    result.coordinates[3].x = c.x;     result.coordinates[3].y = c.y - 1;
    result.coordinates[4].x = c.x;     result.coordinates[4].y = c.y + 1;
    result.coordinates[5].x = c.x + 1; result.coordinates[5].y = c.y - 1;
    result.coordinates[6].x = c.x + 1; result.coordinates[6].y = c.y;
    result.coordinates[7].x = c.x + 1; result.coordinates[7].y = c.y + 1;
    return result;
}

int main() {
    Coordinate c = {2, 2};
    AdjacentCoordinates adj = get_adjacent_coordinates(c);
    for(int i = 0; i < adj.count; i++) {
        printf("Adjacent coordinate %d: (%d, %d)\n", i+1, adj.coordinates[i].x, adj.coordinates[i].y);
    }
    return 0;
}