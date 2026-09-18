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

int find_largest_inscribed_triangle(double a, double b, Triangle *triangle) {
    double root3;

    if (a <= 0.0 || b <= 0.0 || triangle == NULL) {
        return -1;
    }

    root3 = sqrt(3.0);

    triangle->v1.x = a;
    triangle->v1.y = 0.0;

    triangle->v2.x = -a / 2.0;
    triangle->v2.y = (b * root3) / 2.0;

    triangle->v3.x = -a / 2.0;
    triangle->v3.y = -(b * root3) / 2.0;

    triangle->area = (3.0 * root3 * a * b) / 4.0;

    return 0;
}

int main(void) {
    double a = 5.0;
    double b = 3.0;
    Triangle t;

    if (find_largest_inscribed_triangle(a, b, &t) != 0) {
        fprintf(stderr, "Error: Invalid ellipse parameters or null pointer.\n");
        return EXIT_FAILURE;
    }

    printf("Vertex 1: (%.6f, %.6f)\n", t.v1.x, t.v1.y);
    printf("Vertex 2: (%.6f, %.6f)\n", t.v2.x, t.v2.y);
    printf("Vertex 3: (%.6f, %.6f)\n", t.v3.x, t.v3.y);
    printf("Maximal Area: %.6f\n", t.area);

    return EXIT_SUCCESS;
}