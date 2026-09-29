#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    double area;
    double base;
    double height;
} Triangle;

typedef struct {
    Triangle largest_triangle;
} SemicircleResult;

SemicircleResult find_largest_inscribed_triangle(double radius) {
    SemicircleResult result;
    if (radius <= 0) {
        result.largest_triangle.area = 0;
        result.largest_triangle.base = 0;
        result.largest_triangle.height = 0;
        return result;
    }
    double base = 2.0 * radius;
    double height = radius;
    result.largest_triangle.base = base;
    result.largest_triangle.height = height;
    result.largest_triangle.area = 0.5 * base * height;
    return result;
}

int main(void) {
    double radius = 1.0;
    SemicircleResult result = find_largest_inscribed_triangle(radius);
    printf("Radius: %.2f\n", radius);
    printf("Largest triangle base: %.2f\n", result.largest_triangle.base);
    printf("Largest triangle height: %.2f\n", result.largest_triangle.height);
    printf("Largest triangle area: %.2f\n", result.largest_triangle.area);
    return EXIT_SUCCESS;
}