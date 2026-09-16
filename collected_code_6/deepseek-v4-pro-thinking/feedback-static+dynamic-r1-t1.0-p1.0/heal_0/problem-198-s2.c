#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <float.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[3];
    double area;
} Triangle;

int largest_inscribed_triangle(double a, double b, Triangle *out);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <semi-axis-x> <semi-axis-y>\n", argv[0]);
        return 1;
    }

    char *end = NULL;
    errno = 0;
    double a = strtod(argv[1], &end);
    if (end == argv[1] || *end != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid x semi-axis.\n");
        return 1;
    }

    errno = 0;
    double b = strtod(argv[2], &end);
    if (end == argv[2] || *end != '\0' || errno == ERANGE) {
        fprintf(stderr, "Invalid y semi-axis.\n");
        return 1;
    }

    Triangle triangle;
    if (largest_inscribed_triangle(a, b, &triangle) != 0) {
        fprintf(stderr, "Axes must be finite and positive.\n");
        return 1;
    }

    printf("Area: %.15f\n", triangle.area);
    for (int i = 0; i < 3; ++i) {
        printf("Vertex %d: (%.15f, %.15f)\n", i + 1,
               triangle.vertices[i].x, triangle.vertices[i].y);
    }

    return 0;
}

int largest_inscribed_triangle(double a, double b, Triangle *out) {
    if (!(a > 0.0) || !(b > 0.0) || a > DBL_MAX || b > DBL_MAX || out == NULL) {
        return -1;
    }

    if (a > DBL_MAX / b) {
        return -1;
    }

    const double area_factor = 3.0 * sqrt(3.0) / 4.0;
    if (a * b > DBL_MAX / area_factor) {
        return -1;
    }

    const double root3_over_2 = sqrt(3.0) / 2.0;

    out->vertices[0].x = a;
    out->vertices[0].y = 0.0;
    out->vertices[1].x = -0.5 * a;
    out->vertices[1].y = root3_over_2 * b;
    out->vertices[2].x = -0.5 * a;
    out->vertices[2].y = -root3_over_2 * b;
    out->area = area_factor * a * b;

    return 0;
}