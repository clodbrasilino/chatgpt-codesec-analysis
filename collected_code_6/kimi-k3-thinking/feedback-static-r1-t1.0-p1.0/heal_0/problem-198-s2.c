#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[3];
    double area;
} InscribedTriangle;

bool largest_inscribed_triangle(double a, double b, InscribedTriangle *result)
{
    if (result == NULL) {
        return false;
    }
    if (!isfinite(a) || !isfinite(b) || a <= 0.0 || b <= 0.0) {
        return false;
    }

    const double angles[3] = {
        0.0,
        2.0 * M_PI / 3.0,
        4.0 * M_PI / 3.0
    };

    for (size_t i = 0; i < 3; ++i) {
        result->vertices[i].x = a * cos(angles[i]);
        result->vertices[i].y = b * sin(angles[i]);
        if (!isfinite(result->vertices[i].x) || !isfinite(result->vertices[i].y)) {
            return false;
        }
    }

    result->area = (3.0 * sqrt(3.0) / 4.0) * a * b;
    if (!isfinite(result->area)) {
        return false;
    }

    return true;
}

int main(void)
{
    double a = 0.0;
    double b = 0.0;
    InscribedTriangle triangle = { {{0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0}}, 0.0 };

    printf("Enter semi-axis a of the ellipse: ");
    if (scanf("%lf", &a) != 1) {
        fprintf(stderr, "Error: invalid input for semi-axis a.\n");
        return EXIT_FAILURE;
    }

    printf("Enter semi-axis b of the ellipse: ");
    if (scanf("%lf", &b) != 1) {
        fprintf(stderr, "Error: invalid input for semi-axis b.\n");
        return EXIT_FAILURE;
    }

    if (!largest_inscribed_triangle(a, b, &triangle)) {
        fprintf(stderr, "Error: semi-axes must be positive finite numbers.\n");
        return EXIT_FAILURE;
    }

    printf("Largest inscribed triangle area: %.6f\n", triangle.area);
    for (size_t i = 0; i < 3; ++i) {
        printf("Vertex %zu: (%.6f, %.6f)\n",
               i + 1,
               triangle.vertices[i].x,
               triangle.vertices[i].y);
    }

    return EXIT_SUCCESS;
}