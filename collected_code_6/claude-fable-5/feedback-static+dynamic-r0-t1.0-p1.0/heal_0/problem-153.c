#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Vertex;

int find_parabola_vertex(double a, double b, double c, Vertex *result)
{
    if (result == NULL) {
        return -1;
    }

    if (fabs(a) < 1e-12) {
        return -1;
    }

    result->x = -b / (2.0 * a);
    result->y = c - (b * b) / (4.0 * a);

    if (isnan(result->x) || isnan(result->y) ||
        isinf(result->x) || isinf(result->y)) {
        return -1;
    }

    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    Vertex v;

    printf("Enter coefficients a, b, c of the parabola (y = ax^2 + bx + c): ");

    if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
        fprintf(stderr, "Error: invalid input.\n");
        return EXIT_FAILURE;
    }

    if (find_parabola_vertex(a, b, c, &v) != 0) {
        fprintf(stderr, "Error: cannot compute vertex (a must be nonzero and inputs must be finite).\n");
        return EXIT_FAILURE;
    }

    printf("Vertex: (%.6f, %.6f)\n", v.x, v.y);

    return EXIT_SUCCESS;
}