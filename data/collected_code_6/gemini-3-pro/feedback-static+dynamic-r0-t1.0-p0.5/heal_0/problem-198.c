#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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

Triangle find_largest_inscribed_triangle(double a, double b) {
    Triangle max_triangle = {0};
    
    if (a <= 0.0 || b <= 0.0) {
        return max_triangle;
    }

    double theta1 = 0.0;
    double theta2 = 2.0 * M_PI / 3.0;
    double theta3 = 4.0 * M_PI / 3.0;

    max_triangle.p1.x = a * cos(theta1);
    max_triangle.p1.y = b * sin(theta1);

    max_triangle.p2.x = a * cos(theta2);
    max_triangle.p2.y = b * sin(theta2);

    max_triangle.p3.x = a * cos(theta3);
    max_triangle.p3.y = b * sin(theta3);

    max_triangle.area = (3.0 * sqrt(3.0) / 4.0) * a * b;

    return max_triangle;
}

int main(void) {
    double a = 5.0;
    double b = 3.0;

    Triangle t = find_largest_inscribed_triangle(a, b);

    if (t.area > 0.0) {
        printf("Largest inscribed triangle in ellipse (a=%.2f, b=%.2f):\n", a, b);
        printf("Point 1: (%.2f, %.2f)\n", t.p1.x, t.p1.y);
        printf("Point 2: (%.2f, %.2f)\n", t.p2.x, t.p2.y);
        printf("Point 3: (%.2f, %.2f)\n", t.p3.x, t.p3.y);
        printf("Area: %.2f\n", t.area);
    } else {
        printf("Invalid ellipse dimensions.\n");
    }

    return 0;
}