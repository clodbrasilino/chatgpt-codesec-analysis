#include <stdio.h>
#include <math.h>

typedef struct {
    double a;
    double b;
} Ellipse;

typedef struct {
    double base;
    double height;
} Triangle;

Ellipse getEllipse() {
    Ellipse e;
    printf("Enter the semi-major axis length: ");
    scanf("%lf", &e.a);
    printf("Enter the semi-minor axis length: ");
    scanf("%lf", &e.b);
    return e;
}

Triangle inscribedTriangle(Ellipse e) {
    Triangle t;
    t.base = 2 * e.a;
    t.height = 2 * e.b;
    return t;
}

double triangleArea(Triangle t) {
    return 0.5 * t.base * t.height;
}

int main() {
    Ellipse e = getEllipse();
    Triangle t = inscribedTriangle(e);
    double area = triangleArea(t);
    printf("The largest triangle that can be inscribed in the given ellipse has an area of %.2lf\n", area);
    return 0;
}