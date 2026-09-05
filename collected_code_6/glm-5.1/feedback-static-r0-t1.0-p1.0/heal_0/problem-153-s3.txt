#include <stdio.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

int find_parabola_vertex(double a, double b, double c, Point *vertex) {
    if (vertex == NULL) {
        return -1;
    }
    
    if (a == 0.0) {
        return -2;
    }

    vertex->x = -b / (2.0 * a);
    vertex->y = c - (b * b) / (4.0 * a);

    return 0;
}

int main() {
    double a, b, c;
    Point vertex;

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        return 1;
    }

    int result = find_parabola_vertex(a, b, c, &vertex);
    
    if (result == 0) {
        printf("Vertex: (%f, %f)\n", vertex.x, vertex.y);
    } else if (result == -2) {
        printf("Coefficient 'a' cannot be zero.\n");
    } else {
        printf("Invalid input.\n");
    }

    return 0;
}