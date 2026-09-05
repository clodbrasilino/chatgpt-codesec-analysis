#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coord;

Coord* get_adjacent(Coord c, int* count) {
    Coord* adj = malloc(8 * sizeof(Coord));
    if (!adj) {
        *count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Variable 'dx' can be declared as const array [constVariable]
     */
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    /* Possible weaknesses found:
     *  Variable 'dy' can be declared as const array [constVariable]
     */
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; i++) {
        adj[i].x = c.x + dx[i];
        adj[i].y = c.y + dy[i];
    }

    *count = 8;
    return adj;
}

int main() {
    Coord c = {2, 2};
    int count;
    Coord* adj = get_adjacent(c, &count);

    if (adj) {
        for (int i = 0; i < count; i++) {
            printf("(%d, %d)\n", adj[i].x, adj[i].y);
        }
        free(adj);
    }

    return 0;
}