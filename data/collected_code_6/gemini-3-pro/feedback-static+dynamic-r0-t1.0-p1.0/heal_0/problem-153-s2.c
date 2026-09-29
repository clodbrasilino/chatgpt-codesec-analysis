#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

Point* find_vertex(double a, double b, double c) {
    if (a == 0.0) {
        return NULL;
    }

    Point* vertex = (Point*)malloc(sizeof(Point));
    if (vertex == NULL) {
        return NULL;
    }

    vertex->x = -b / (2 * a);
    vertex->y = a * (vertex->x * vertex->x) + b * vertex->x + c;

    return vertex;
}

int main(void) {
    double a = 1.0;
    double b = -4.0;
    double c = 4.0;

    Point* vertex = find_vertex(a, b, c);

    if (vertex != NULL) {
        printf("Vertex: (%.2f, %.2f)\n", vertex->x, vertex->y);
        free(vertex);
    } else {
        printf("Invalid parabola coefficients or memory allocation failed.\n");
    }

    return 0;
}