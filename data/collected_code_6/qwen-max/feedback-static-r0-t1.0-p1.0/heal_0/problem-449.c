#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double calculate_distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

int is_valid_triangle(Point a, Point b, Point c) {
    double ab = calculate_distance(a, b);
    double bc = calculate_distance(b, c);
    double ca = calculate_distance(c, a);

    if (ab + bc > ca && bc + ca > ab && ca + ab > bc) {
        return 1;
    }
    return 0;
}

int main() {
    Point a = {0.0, 0.0};
    Point b = {4.0, 0.0};
    Point c = {2.0, 3.0};

    if (is_valid_triangle(a, b, c)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }

    return 0;
}