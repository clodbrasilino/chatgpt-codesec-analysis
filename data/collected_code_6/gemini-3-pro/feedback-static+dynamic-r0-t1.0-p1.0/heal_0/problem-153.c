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
    vertex->y = a * (vertex->x * vertex->x) + b * vertex->x + c;

    return 0;
}

int main(void) {
    double a, b, c;
    Vertex v;

    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input.\n");
        return EXIT_FAILURE;
    }

    if (find_vertex(a, b, c, &v) == 0) {
        printf("The vertex of the parabola is at (%.2lf, %.2lf)\n", v.x, v.y);
    } else {
        fprintf(stderr, "Error: 'a' cannot be zero for a parabola.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}