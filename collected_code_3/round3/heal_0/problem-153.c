#include <stdio.h>
#include <math.h>

struct Point {
    double x;
    double y;
};

struct Parabola {
    double a;
    double b;
    double c;
};

struct Point findVertex(struct Parabola p) {
    struct Point vertex;
    vertex.x = -p.b / (2 * p.a);
    vertex.y = p.c - p.b * p.b / (4 * p.a);
    return vertex;
}

int main() {
    struct Parabola p;
    p.a = 1;
    p.b = -2;
    p.c = 1;

    struct Point vertex = findVertex(p);

    printf("Vertex of the parabola is at (%f, %f)\n", vertex.x, vertex.y);

    return 0;
}