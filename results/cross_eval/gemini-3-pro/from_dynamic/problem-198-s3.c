#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point p1;
    Point p2;
    Point p3;
    double area;
} Triangle;

Triangle findLargestTriangleInEllipse(double a, double b) {
    Triangle maxTriangle = {0};

    if (a <= 0 || b <= 0) {
        return maxTriangle;
    }

    maxTriangle.p1.x = a;
    maxTriangle.p1.y = 0.0;

    maxTriangle.p2.x = -a / 2.0;
    maxTriangle.p2.y = b * sqrt(3.0) / 2.0;

    maxTriangle.p3.x = -a / 2.0;
    maxTriangle.p3.y = -b * sqrt(3.0) / 2.0;

    maxTriangle.area = (3.0 * sqrt(3.0) / 4.0) * a * b;

    return maxTriangle;
}

int main(void) {
    double a = 5.0;
    double b = 3.0;

    Triangle largestTriangle = findLargestTriangleInEllipse(a, b);

    if (largestTriangle.area > 0.0) {
        printf("Point 1: (%.2f, %.2f)\n", largestTriangle.p1.x, largestTriangle.p1.y);
        printf("Point 2: (%.2f, %.2f)\n", largestTriangle.p2.x, largestTriangle.p2.y);
        printf("Point 3: (%.2f, %.2f)\n", largestTriangle.p3.x, largestTriangle.p3.y);
        printf("Max Area: %.2f\n", largestTriangle.area);
    } else {
        printf("Invalid ellipse dimensions.\n");
    }

    return 0;
}