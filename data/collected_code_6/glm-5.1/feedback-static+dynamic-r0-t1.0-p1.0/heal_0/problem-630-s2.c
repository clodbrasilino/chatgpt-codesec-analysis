#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coordinate;

Coordinate* get_adjacent_coordinates(Coordinate c, int* count) {
    Coordinate* adj = malloc(8 * sizeof(Coordinate));
    if (adj == NULL) {
        *count = 0;
        return NULL;
    }

    adj[0].x = c.x - 1;
    adj[0].y = c.y - 1;

    adj[1].x = c.x - 1;
    adj[1].y = c.y;

    adj[2].x = c.x - 1;
    adj[2].y = c.y + 1;

    adj[3].x = c.x;
    adj[3].y = c.y - 1;

    adj[4].x = c.x;
    adj[4].y = c.y + 1;

    adj[5].x = c.x + 1;
    adj[5].y = c.y - 1;

    adj[6].x = c.x + 1;
    adj[6].y = c.y;

    adj[7].x = c.x + 1;
    adj[7].y = c.y + 1;

    *count = 8;
    return adj;
}

int main() {
    Coordinate c = {3, 3};
    int count = 0;
    Coordinate* adj = get_adjacent_coordinates(c, &count);

    if (adj == NULL) {
        return 1;
    }

    for (int i = 0; i < count; i++) {
        printf("(%d, %d)\n", adj[i].x, adj[i].y);
    }

    free(adj);
    adj = NULL;

    return 0;
}