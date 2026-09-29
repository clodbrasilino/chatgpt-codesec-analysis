#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double x;
    double y;
} Point;

double largest_inscribed_triangle(double a, double b, Point triangle[3]) {
    if (a <= 0.0 || b <= 0.0 || !isfinite(a) || !isfinite(b) || triangle == NULL) {
        return -1.0;
    }

    double s3 = sqrt(3.0);
    triangle[0].x = a;
    triangle[0].y = 0.0;
    triangle[1].x = -0.5 * a;
    triangle[1].y = 0.5 * b * s3;
    triangle[2].x = -0.5 * a;
    triangle[2].y = -0.5 * b * s3;

    return 0.75 * s3 * a * b;
}

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <a> <b>\n", argv[0]);
        return EXIT_FAILURE;
    }

    char *endptr_a = NULL;
    char *endptr_b = NULL;
    double a = strtod(argv[1], &endptr_a);
    double b = strtod(argv[2], &endptr_b);

    if (endptr_a == argv[1] || *endptr_a != '\0' ||
        endptr_b == argv[2] || *endptr_b != '\0' ||
        !isfinite(a) || !isfinite(b) ||
        a <= 0.0 || b <= 0.0) {
        fprintf(stderr, "Error: a and b must be positive numbers.\n");
        return EXIT_FAILURE;
    }

    Point triangle[3];
    double area = largest_inscribed_triangle(a, b, triangle);

    if (area < 0.0) {
        fprintf(stderr, "Error: unable to compute triangle.\n");
        return EXIT_FAILURE;
    }

    printf("Vertices:\n");
    printf("  (%.15g, %.15g)\n", triangle[0].x, triangle[0].y);
    printf("  (%.15g, %.15g)\n", triangle[1].x, triangle[1].y);
    printf("  (%.15g, %.15g)\n", triangle[2].x, triangle[2].y);
    printf("Area: %.15g\n", area);
    return EXIT_SUCCESS;
}