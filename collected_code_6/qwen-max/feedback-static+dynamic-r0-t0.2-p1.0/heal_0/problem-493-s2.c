#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point *points;
    size_t count;
} PointList;

PointList* create_point_list(size_t count) {
    PointList *list = (PointList*)malloc(sizeof(PointList));
    if (!list) return NULL;
    list->points = (Point*)malloc(count * sizeof(Point));
    if (!list->points) {
        free(list);
        return NULL;
    }
    list->count = count;
    return list;
}

void free_point_list(PointList *list) {
    if (list) {
        free(list->points);
        free(list);
    }
}

PointList* calculate_hexagon(int center_x, int center_y, int radius) {
    PointList *hexagon = create_point_list(6);
    if (!hexagon) return NULL;

    hexagon->points[0] = (Point){center_x + 2 * radius, center_y};
    hexagon->points[1] = (Point){center_x + radius, center_y - radius};
    hexagon->points[2] = (Point){center_x - radius, center_y - radius};
    hexagon->points[3] = (Point){center_x - 2 * radius, center_y};
    hexagon->points[4] = (Point){center_x - radius, center_y + radius};
    hexagon->points[5] = (Point){center_x + radius, center_y + radius};

    return hexagon;
}

int main() {
    int center_x = 50;
    int center_y = 50;
    int radius = 10;

    PointList *hexagon = calculate_hexagon(center_x, center_y, radius);
    if (hexagon) {
        for (size_t i = 0; i < hexagon->count; ++i) {
            printf("(%d, %d)\n", hexagon->points[i].x, hexagon->points[i].y);
        }
        free_point_list(hexagon);
    }

    return 0;
}