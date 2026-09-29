#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

Coordinate* get_adjacent_coordinates(Coordinate coord, int* count) {
    if (!count) {
        return NULL;
    }

    *count = 8;
    Coordinate* adj_coords = (Coordinate*)malloc(*count * sizeof(Coordinate));
    if (!adj_coords) {
        *count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Variable 'dx' can be declared as const array [constVariable]
     */
    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    /* Possible weaknesses found:
     *  Variable 'dy' can be declared as const array [constVariable]
     */
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for (int i = 0; i < *count; i++) {
        adj_coords[i].x = coord.x + dx[i];
        adj_coords[i].y = coord.y + dy[i];
    }

    return adj_coords;
}

int main(void) {
    Coordinate my_coord = {5, 5};
    int count = 0;

    Coordinate* adj_coords = get_adjacent_coordinates(my_coord, &count);

    if (adj_coords) {
        printf("Adjacent coordinates for (%d, %d):\n", my_coord.x, my_coord.y);
        for (int i = 0; i < count; i++) {
            printf("(%d, %d)\n", adj_coords[i].x, adj_coords[i].y);
        }
        free(adj_coords);
        adj_coords = NULL;
    } else {
        printf("Failed to allocate memory or invalid arguments.\n");
    }

    return 0;
}