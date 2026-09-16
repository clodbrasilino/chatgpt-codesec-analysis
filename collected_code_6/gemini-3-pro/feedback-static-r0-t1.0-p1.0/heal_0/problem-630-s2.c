#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

Coordinate* get_adjacent_coordinates(Coordinate coord, int* count) {
    if (count == NULL) {
        return NULL;
    }

    *count = 8;
    Coordinate* adj_coords = (Coordinate*)malloc(8 * sizeof(Coordinate));
    if (adj_coords == NULL) {
        *count = 0;
        return NULL;
    }

    int idx = 0;
    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0) {
                continue;
            }
            adj_coords[idx].x = coord.x + dx;
            adj_coords[idx].y = coord.y + dy;
            idx++;
        }
    }

    return adj_coords;
}

int main(void) {
    Coordinate coord = {5, 5};
    int count = 0;

    Coordinate* adj_coords = get_adjacent_coordinates(coord, &count);

    if (adj_coords != NULL) {
        for (int i = 0; i < count; i++) {
            printf("(%d, %d)\n", adj_coords[i].x, adj_coords[i].y);
        }
        free(adj_coords);
    } else {
        printf("Failed to allocate memory or invalid arguments.\n");
    }

    return 0;
}