#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long double x;
    long double y;
} Point;

typedef struct {
    Point vertices[3];
    long double area;
} Triangle;

bool find_largest_inscribed_triangle(long double semi_axis_x,
                                     long double semi_axis_y,
                                     Triangle *triangle)
{
    long double sqrt_three;
    long double area_factor;
    long double maximum_product;

    if (triangle == NULL ||
        !isfinite(semi_axis_x) ||
        !isfinite(semi_axis_y) ||
        semi_axis_x <= 0.0L ||
        semi_axis_y <= 0.0L) {
        return false;
    }

    sqrt_three = sqrtl(3.0L);
    area_factor = 3.0L * sqrt_three / 4.0L;
    maximum_product = LDBL_MAX / area_factor;

    if (semi_axis_x > maximum_product / semi_axis_y) {
        return false;
    }

    triangle->vertices[0] = (Point){semi_axis_x, 0.0L};
    triangle->vertices[1] = (Point){
        -semi_axis_x / 2.0L,
        sqrt_three * semi_axis_y / 2.0L
    };
    triangle->vertices[2] = (Point){
        -semi_axis_x / 2.0L,
        -sqrt_three * semi_axis_y / 2.0L
    };
    triangle->area = (semi_axis_x * semi_axis_y) * area_factor;

    return isfinite(triangle->area);
}

int main(void)
{
    long double semi_axis_x;
    long double semi_axis_y;
    Triangle triangle;

    if (scanf("%Lf %Lf", &semi_axis_x, &semi_axis_y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }

    if (!find_largest_inscribed_triangle(
            semi_axis_x, semi_axis_y, &triangle)) {
        fprintf(stderr, "Unable to calculate the triangle\n");
        return EXIT_FAILURE;
    }

    printf("Area: %.10Lf\n", triangle.area);

    for (size_t i = 0; i < 3; ++i) {
        printf("Vertex %zu: (%.10Lf, %.10Lf)\n",
               i + 1,
               triangle.vertices[i].x,
               triangle.vertices[i].y);
    }

    return EXIT_SUCCESS;
}