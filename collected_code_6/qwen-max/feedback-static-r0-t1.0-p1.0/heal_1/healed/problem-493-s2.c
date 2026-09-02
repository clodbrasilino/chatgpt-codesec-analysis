#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point* points;
    int size;
} PointsList;

void free_points_list(PointsList plist) {
    if (plist.points) {
        free(plist.points);
    }
}

PointsList calculate_hexagon(double cx, double cy, double radius) {
    PointsList plist;
    plist.points = (Point*) malloc(6 * sizeof(Point));
    if (plist.points == NULL) {
        exit(EXIT_FAILURE);
    }
    plist.size = 6;

    for (int i = 0; i < 6; ++i) {
        double angle_deg = 60 * i - 30;
        double angle_rad = M_PI / 180 * angle_deg;
        plist.points[i].x = cx + radius * cos(angle_rad);
        plist.points[i].y = cy + radius * sin(angle_rad);
    }

    return plist;
}

int main() {
    double center_x = 0.0;
    double center_y = 0.0;
    double radius = 10.0;

    PointsList hexagon = calculate_hexagon(center_x, center_y, radius);

    for (int i = 0; i < hexagon.size; ++i) {
        printf("Point %d: (%.2f, %.2f)\n", i+1, hexagon.points[i].x, hexagon.points[i].y);
    }

    free_points_list(hexagon);

    return 0;
}