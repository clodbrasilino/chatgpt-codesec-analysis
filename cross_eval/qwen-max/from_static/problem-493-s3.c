#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point points[6];
    int size;
} Hexagon;

Hexagon* create_hexagon(int center_x, int center_y, int radius) {
    Hexagon* hexagon = (Hexagon*)malloc(sizeof(Hexagon));
    if (hexagon == NULL) return NULL;

    hexagon->points[0].x = center_x + 2 * radius; hexagon->points[0].y = center_y;
    hexagon->points[1].x = center_x + radius; hexagon->points[1].y = center_y - radius;
    hexagon->points[2].x = center_x - radius; hexagon->points[2].y = center_y - radius;
    hexagon->points[3].x = center_x - 2 * radius; hexagon->points[3].y = center_y;
    hexagon->points[4].x = center_x - radius; hexagon->points[4].y = center_y + radius;
    hexagon->points[5].x = center_x + radius; hexagon->points[5].y = center_y + radius;

    hexagon->size = 6;
    return hexagon;
}

int main() {
    Hexagon* hexagon = create_hexagon(10, 10, 5);
    if (hexagon == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 0; i < hexagon->size; i++) {
        printf("Point %d: (%d, %d)\n", i+1, hexagon->points[i].x, hexagon->points[i].y);
    }

    free(hexagon);
    return 0;
}