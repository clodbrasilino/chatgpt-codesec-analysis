#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    int size;
    Point *points;
} PointsList;

PointsList* create_hexagon(double center_x, double center_y, double radius) {
    PointsList* hex = (PointsList*)malloc(sizeof(PointsList));
    if (hex == NULL) {
        return NULL;
    }
    hex->size = 6;
    hex->points = (Point*)malloc(hex->size * sizeof(Point));
    if (hex->points == NULL) {
        free(hex);
        return NULL;
    }

    for (int i = 0; i < 6; ++i) {
        double angle_deg = 60 * i - 30;
        double angle_rad = angle_deg * M_PI / 180.0;
        hex->points[i].x = center_x + radius * cos(angle_rad);
        hex->points[i].y = center_y + radius * sin(angle_rad);
    }

    return hex;
}

void print_hexagon(PointsList *hex) {
    for (int i = 0; i < hex->size; ++i) {
        printf("(%.2f, %.2f)\n", hex->points[i].x, hex->points[i].y);
    }
}

void free_points_list(PointsList *list) {
    free(list->points);
    free(list);
}

int main() {
    double center_x = 0.0;
    double center_y = 0.0;
    double radius = 1.0;

    PointsList *hex = create_hexagon(center_x, center_y, radius);
    if (hex != NULL) {
        print_hexagon(hex);
        free_points_list(hex);
    } else {
        fprintf(stderr, "Failed to create hexagon\n");
        return 1;
    }

    return 0;
}