#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point v1;
    Point v2;
    Point v3;
    double area;
} Triangle;

int find_largest_triangle_in_ellipse(double a, double b, Triangle *triangle);

int find_largest_triangle_in_ellipse(double a, double b, Triangle *triangle) {
    if (a <= 0.0 || b <= 0.0 || triangle == NULL) {
        return -1;
    }

    double sqrt3 = sqrt(3.0);

    triangle->v1.x = a;
    triangle->v1.y = 0.0;

    triangle->v2.x = -a / 2.0;
    triangle->v2.y = (b * sqrt3) / 2.0;

    triangle->v3.x = -a / 2.0;
    triangle->v3.y = -(b * sqrt3) / 2.0;

    triangle->area = (3.0 * sqrt3 / 4.0) * a * b;

    return 0;
}

int main(void) {
    double a = 0.0;
    double b = 0.0;
    Triangle triangle = {0};

    if (scanf("%lf %lf", &a, &b) != 2) {
        return EXIT_FAILURE;
    }

    if (find_largest_triangle_in_ellipse(a, b, &triangle) != 0) {
        return EXIT_FAILURE;
    }

    printf("%.6f %.6f\n", triangle.v1.x, triangle.v1.y);
    printf("%.6f %.6f\n", triangle.v2.x, triangle.v2.y);
    printf("%.6f %.6f\n", triangle.v3.x, triangle.v3.y);
    printf("%.6f\n", triangle.area);

    return EXIT_SUCCESS;
}