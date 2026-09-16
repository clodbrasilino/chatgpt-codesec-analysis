#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double distance(Point a, Point b) {
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

int isValidTriangle(Point p1, Point p2, Point p3) {
    double a = distance(p1, p2);
    double b = distance(p2, p3);
    double c = distance(p3, p1);

    if (a <= 0.0 || b <= 0.0 || c <= 0.0) {
        return 0;
    }

    if ((a + b > c) && (b + c > a) && (c + a > b)) {
        return 1;
    }

    return 0;
}

int main(void) {
    Point p1 = {0.0, 0.0};
    Point p2 = {1.0, 0.0};
    Point p3 = {0.0, 1.0};

    if (isValidTriangle(p1, p2, p3)) {
        printf("Valid triangle\n");
    } else {
        printf("Invalid triangle\n");
    }

    return 0;
}