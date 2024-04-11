#include <stdio.h>
#include <math.h>

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

typedef struct {
    double x;
    double y;
} Vertex;

Vertex findVertex(Parabola p) {
    Vertex v;
    v.x = -p.b / (2 * p.a);
    v.y = p.c - p.b * p.b / (4 * p.a);
    return v;
}

int main() {
    Parabola p;
    p.a = 1;
    p.b = -2;
    p.c = 1;

    Vertex v = findVertex(p);

    printf("Vertex of the parabola is at (%f, %f)\n", v.x, v.y);

    return 0;
}