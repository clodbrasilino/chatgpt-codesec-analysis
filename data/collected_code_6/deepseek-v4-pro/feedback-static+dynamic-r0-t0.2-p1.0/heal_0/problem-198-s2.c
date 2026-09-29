#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

typedef struct {
    double x;
    double y;
} Point;

typedef struct {
    Point a;
    Point b;
    Point c;
    double area;
} Triangle;

double triangle_area(Point a, Point b, Point c) {
    return fabs((a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / 2.0);
}

Triangle largest_inscribed_triangle(double a, double b) {
    Triangle result;
    double theta = 2.0 * PI / 3.0;
    double phi = PI / 2.0;
    
    result.a.x = a * cos(phi);
    result.a.y = b * sin(phi);
    result.b.x = a * cos(phi + theta);
    result.b.y = b * sin(phi + theta);
    result.c.x = a * cos(phi + 2.0 * theta);
    result.c.y = b * sin(phi + 2.0 * theta);
    
    result.area = triangle_area(result.a, result.b, result.c);
    
    return result;
}

int main(void) {
    double semi_major, semi_minor;
    Triangle largest;
    
    printf("Enter semi-major axis (a): ");
    if (scanf("%lf", &semi_major) != 1 || semi_major <= 0) {
        fprintf(stderr, "Invalid input for semi-major axis\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter semi-minor axis (b): ");
    if (scanf("%lf", &semi_minor) != 1 || semi_minor <= 0) {
        fprintf(stderr, "Invalid input for semi-minor axis\n");
        return EXIT_FAILURE;
    }
    
    largest = largest_inscribed_triangle(semi_major, semi_minor);
    
    printf("Largest inscribed triangle vertices:\n");
    printf("A: (%.6f, %.6f)\n", largest.a.x, largest.a.y);
    printf("B: (%.6f, %.6f)\n", largest.b.x, largest.b.y);
    printf("C: (%.6f, %.6f)\n", largest.c.x, largest.c.y);
    printf("Area: %.6f\n", largest.area);
    
    return EXIT_SUCCESS;
}