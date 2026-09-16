#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Vertex;

typedef enum {
    PARABOLA_OK,
    PARABOLA_INVALID_COEFFICIENT,
    PARABOLA_NULL_POINTER
} ParabolaResult;

ParabolaResult find_vertex(double a, double b, double c, Vertex *vertex) {
    if (vertex == NULL) {
        return PARABOLA_NULL_POINTER;
    }
    if (fabs(a) < 1e-12) {
        return PARABOLA_INVALID_COEFFICIENT;
    }
    vertex->x = -b / (2.0 * a);
    vertex->y = a * vertex->x * vertex->x + b * vertex->x + c;
    return PARABOLA_OK;
}

int main(void) {
    double a, b, c;
    Vertex vertex;
    ParabolaResult result;

    printf("Enter coefficients a, b, c: ");
    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    result = find_vertex(a, b, c, &vertex);

    if (result == PARABOLA_OK) {
        printf("Vertex: (%.6f, %.6f)\n", vertex.x, vertex.y);
        return EXIT_SUCCESS;
    } else if (result == PARABOLA_INVALID_COEFFICIENT) {
        fprintf(stderr, "Error: coefficient 'a' must be non-zero\n");
        return EXIT_FAILURE;
    } else if (result == PARABOLA_NULL_POINTER) {
        fprintf(stderr, "Error: internal null pointer\n");
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}