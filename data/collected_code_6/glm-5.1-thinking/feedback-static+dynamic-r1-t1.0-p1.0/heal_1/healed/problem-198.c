#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double largest_inscribed_triangle(double a, double b, Point *v1, Point *v2, Point *v3) {
    if (a <= 0.0 || b <= 0.0) {
        if (v1) { v1->x = 0.0; v1->y = 0.0; }
        if (v2) { v2->x = 0.0; v2->y = 0.0; }
        if (v3) { v3->x = 0.0; v3->y = 0.0; }
        return 0.0;
    }

    double pi = acos(-1.0);

    if (v1) {
        double angle1 = 0.0;
        v1->x = a * cos(angle1);
        v1->y = b * sin(angle1);
    }
    if (v2) {
        double angle2 = 2.0 * pi / 3.0;
        v2->x = a * cos(angle2);
        v2->y = b * sin(angle2);
    }
    if (v3) {
        double angle3 = 4.0 * pi / 3.0;
        v3->x = a * cos(angle3);
        v3->y = b * sin(angle3);
    }

    return (3.0 * sqrt(3.0) / 4.0) * a * b;
}

int main(void) {
    double a = 5.0;
    double b = 3.0;
    Point v1, v2, v3;

    double area = largest_inscribed_triangle(a, b, &v1, &v2, &v3);

    printf("Ellipse semi-major axis (a): %f\n", a);
    printf("Ellipse semi-minor axis (b): %f\n", b);
    printf("Largest inscribed triangle area: %f\n", area);
    printf("Vertices:\n");
    printf("  V1: (%f, %f)\n", v1.x, v1.y);
    printf("  V2: (%f, %f)\n", v2.x, v2.y);
    printf("  V3: (%f, %f)\n", v3.x, v3.y);

    double invalid_area = largest_inscribed_triangle(-5.0, 3.0, NULL, NULL, NULL);
    printf("Invalid ellipse area: %f\n", invalid_area);

    return 0;
}