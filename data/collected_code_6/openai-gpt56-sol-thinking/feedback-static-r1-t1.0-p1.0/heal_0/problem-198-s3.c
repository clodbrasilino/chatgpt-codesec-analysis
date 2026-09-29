#include <stdbool.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point vertices[3];
    double area;
} Triangle;

bool find_largest_inscribed_triangle(double a, double b, Triangle *triangle)
{
    long double sqrt_three;
    long double area;

    if (triangle == NULL || !isfinite(a) || !isfinite(b) || a <= 0.0 || b <= 0.0) {
        return false;
    }

    sqrt_three = sqrtl(3.0L);
    area = (3.0L * sqrt_three * (long double)a * (long double)b) / 4.0L;

    if (!isfinite(area) || area > DBL_MAX) {
        return false;
    }

    triangle->vertices[0].x = a;
    triangle->vertices[0].y = 0.0;
    triangle->vertices[1].x = -a / 2.0;
    triangle->vertices[1].y = (double)(sqrt_three * (long double)b / 2.0L);
    triangle->vertices[2].x = -a / 2.0;
    triangle->vertices[2].y = (double)(-sqrt_three * (long double)b / 2.0L);
    triangle->area = (double)area;

    return true;
}

int main(void)
{
    double semi_axis_x;
    double semi_axis_y;
    Triangle triangle;
    int result;

    result = scanf("%lf %lf", &semi_axis_x, &semi_axis_y);
    if (result != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!find_largest_inscribed_triangle(semi_axis_x, semi_axis_y, &triangle)) {
        fprintf(stderr, "Unable to compute the triangle\n");
        return EXIT_FAILURE;
    }

    result = printf(
        "Area: %.17g\n"
        "Vertices:\n"
        "(%.17g, %.17g)\n"
        "(%.17g, %.17g)\n"
        "(%.17g, %.17g)\n",
        triangle.area,
        triangle.vertices[0].x, triangle.vertices[0].y,
        triangle.vertices[1].x, triangle.vertices[1].y,
        triangle.vertices[2].x, triangle.vertices[2].y
    );

    if (result < 0) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}