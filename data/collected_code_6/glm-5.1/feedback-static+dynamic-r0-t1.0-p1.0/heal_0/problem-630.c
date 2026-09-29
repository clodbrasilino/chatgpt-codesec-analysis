#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Coord;

Coord* get_adjacent(Coord c, int* count) {
    *count = 8;
    Coord* adj = (Coord*)malloc(8 * sizeof(Coord));
    if (adj == NULL) {
        *count = 0;
        return NULL;
    }

    adj[0].x = c.x - 1; adj[0].y = c.y - 1;
    adj[1].x = c.x;     adj[1].y = c.y - 1;
    adj[2].x = c.x + 1; adj[2].y = c.y - 1;
    adj[3].x = c.x - 1; adj[3].y = c.y;
    adj[4].x = c.x + 1; adj[4].y = c.y;
    adj[5].x = c.x - 1; adj[5].y = c.y + 1;
    adj[6].x = c.x;     adj[6].y = c.y + 1;
    adj[7].x = c.x + 1; adj[7].y = c.y + 1;

    return adj;
}

int main() {
    Coord c = {2, 3};
    int count;
    Coord* adj = get_adjacent(c, &count);

    if (adj != NULL) {
        for (int i = 0; i < count; i++) {
            printf("(%d, %d)\n", adj[i].x, adj[i].y);
        }
        free(adj);
    }

    return 0;
}