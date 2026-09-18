#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[3];
} Triangle;

int calculate_largest_inscribed_triangle(double semi_major_axis, double semi_minor_axis, Triangle *triangle, double *area) {
    if (semi_major_axis <= 0.0 || semi_minor_axis <= 0.0) {
        return -1;
    }
    
    if (triangle == NULL || area == NULL) {
        return -1;
    }

    double sqrt3 = sqrt(3.0);

    triangle->vertices[0].x = semi_major_axis;
    triangle->vertices[0].y = 0.0;

    triangle->vertices[1].x = -semi_major_axis / 2.0;
    triangle->vertices[1].y = (semi_minor_axis * sqrt3) / 2.0;

    triangle->vertices[2].x = -semi_major_axis / 2.0;
    triangle->vertices[2].y = -(semi_minor_axis * sqrt3) / 2.0;

    *area = (3.0 * sqrt3 / 4.0) * semi_major_axis * semi_minor_axis;

    return 0;
}

int main(void) {
    double a = 10.0;
    double b = 5.0;
    
    Triangle largest_triangle;
    double max_area = 0.0;

    int status = calculate_largest_inscribed_triangle(a, b, &largest_triangle, &max_area);

    if (status != 0) {
        fprintf(stderr, "Error: Invalid ellipse parameters or null pointers provided.\n");
        return EXIT_FAILURE;
    }

    printf("Largest Inscribed Triangle Area: %f\n", max_area);
    printf("Vertex 1: (%.4f, %.4f)\n", largest_triangle.vertices[0].x, largest_triangle.vertices[0].y);
    printf("Vertex 2: (%.4f, %.4f)\n", largest_triangle.vertices[1].x, largest_triangle.vertices[1].y);
    printf("Vertex 3: (%.4f, %.4f)\n", largest_triangle.vertices[2].x, largest_triangle.vertices[2].y);

    return EXIT_SUCCESS;
}