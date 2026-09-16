#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Vertex;

int find_vertex(double a, double b, double c, Vertex *vertex) {
    if (vertex == NULL) {
        return -1;
    }

    if (a == 0.0) {
        return -1;
    }

    vertex->x = -b / (2.0 * a);
    vertex->y = (a * vertex->x * vertex->x) + (b * vertex->x) + c;

    return 0;
}

int main(void) {
    double a = 1.0;
    double b = -4.0;
    double c = 4.0;
    Vertex v;

    if (find_vertex(a, b, c, &v) == 0) {
        printf("Vertex: (%.2f, %.2f)\n", v.x, v.y);
    } else {
        printf("Error: Not a valid parabola.\n");
    }

    return 0;
}