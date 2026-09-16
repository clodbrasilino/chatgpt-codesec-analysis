#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

int isValidTriangle(Point p1, Point p2, Point p3) {
    double area = 0.5 * ((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
    return fabs(area) > 1e-9;
}

int main() {
    Point p1, p2, p3;
    printf("Enter coordinates of point 1 (x y): ");
    scanf("%lf %lf", &p1.x, &p1.y);
    printf("Enter coordinates of point 2 (x y): ");
    scanf("%lf %lf", &p2.x, &p2.y);
    printf("Enter coordinates of point 3 (x y): ");
    scanf("%lf %lf", &p3.x, &p3.y);
    if (isValidTriangle(p1, p2, p3)) {
        printf("The triangle is valid.\n");
    } else {
        printf("The triangle is not valid.\n");
    }
    return 0;
}