#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

int is_valid_triangle(Point p1, Point p2, Point p3) {
    double area = (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0;
    if (area < 0) {
        area = -area;
    }
    return area > 1e-9;
}

int main(void) {
    Point points[3];
    for (int i = 0; i < 3; i++) {
        if (scanf("%lf %lf", &points[i].x, &points[i].y) != 2) {
            return EXIT_FAILURE;
        }
    }
    if (is_valid_triangle(points[0], points[1], points[2])) {
        printf("1\n");
    } else {
        printf("0\n");
    }
    return EXIT_SUCCESS;
}