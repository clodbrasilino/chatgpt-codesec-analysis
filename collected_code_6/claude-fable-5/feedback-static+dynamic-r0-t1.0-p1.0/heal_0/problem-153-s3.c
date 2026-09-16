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
    result->y = a * result->x * result->x + b * result->x + c;
    return 0;
}

int main(void)
{
    double a;
    double b;
    double c;
    Vertex vertex;

    printf("Enter coefficient a: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Invalid input for a\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient b: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Invalid input for b\n");
        return EXIT_FAILURE;
    }

    printf("Enter coefficient c: ");
    if (scanf("%lf", &c) != 1) {
        fprintf(stderr, "Invalid input for c\n");
        return EXIT_FAILURE;
    }

    if (find_parabola_vertex(a, b, c, &vertex) != 0) {
        fprintf(stderr, "Error: not a valid parabola (a must be nonzero)\n");
        return EXIT_FAILURE;
    }

    printf("Vertex: (%.6f, %.6f)\n", vertex.x, vertex.y);

    return EXIT_SUCCESS;
}