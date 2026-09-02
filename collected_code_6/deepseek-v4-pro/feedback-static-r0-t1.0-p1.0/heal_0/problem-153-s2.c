#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Vertex;

typedef struct {
    double a;
    double b;
    double c;
} Parabola;

Vertex find_vertex(const Parabola *p) {
    Vertex v;
    if (p->a == 0.0) {
        fprintf(stderr, "Error: Coefficient 'a' cannot be zero.\n");
        exit(EXIT_FAILURE);
    }
    v.x = -p->b / (2.0 * p->a);
    v.y = p->a * v.x * v.x + p->b * v.x + p->c;
    return v;
}

int main(void) {
    Parabola p;
    Vertex v;

    printf("Enter coefficients a, b, and c: ");
    if (scanf("%lf %lf %lf", &p.a, &p.b, &p.c) != 3) {
        fprintf(stderr, "Error: Invalid input.\n");
        return EXIT_FAILURE;
    }

    v = find_vertex(&p);
    printf("Vertex: (%.2f, %.2f)\n", v.x, v.y);

    return EXIT_SUCCESS;
}