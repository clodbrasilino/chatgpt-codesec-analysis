#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <float.h>

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

static double calculate_area(Point p1, Point p2, Point p3) {
    double area = 0.5 * fabs(p1.x * (p2.y - p3.y) + 
                             p2.x * (p3.y - p1.y) + 
                             p3.x * (p1.y - p2.y));
    return area;
}

static int is_point_on_semicircle(Point p, double radius, double center_x, double center_y) {
    double dx = p.x - center_x;
    double dy = p.y - center_y;
    double dist_sq = dx * dx + dy * dy;
    double radius_sq = radius * radius;
    
    if (fabs(dist_sq - radius_sq) > 1e-9) {
        return 0;
    }
    
    if (p.y < center_y - 1e-9) {
        return 0;
    }
    
    return 1;
}

static int is_valid_triangle(Point p1, Point p2, Point p3, double radius, double center_x, double center_y) {
    if (!is_point_on_semicircle(p1, radius, center_x, center_y) ||
        !is_point_on_semicircle(p2, radius, center_x, center_y) ||
        !is_point_on_semicircle(p3, radius, center_x, center_y)) {
        return 0;
    }
    
    double area = calculate_area(p1, p2, p3);
    if (area < 1e-9) {
        return 0;
    }
    
    return 1;
}

static Triangle find_largest_triangle(double radius, double center_x, double center_y) {
    Triangle largest = {{0, 0}, {0, 0}, {0, 0}, 0.0};
    
    if (radius <= 0.0) {
        return largest;
    }
    
    Point left_end = {center_x - radius, center_y};
    Point right_end = {center_x + radius, center_y};
    Point top = {center_x, center_y + radius};
    
    if (is_valid_triangle(left_end, right_end, top, radius, center_x, center_y)) {
        largest.a = left_end;
        largest.b = right_end;
        largest.c = top;
        largest.area = calculate_area(left_end, right_end, top);
    }
    
    return largest;
}

static void print_triangle(Triangle t) {
    printf("Largest triangle vertices:\n");
    printf("A: (%.6f, %.6f)\n", t.a.x, t.a.y);
    printf("B: (%.6f, %.6f)\n", t.b.x, t.b.y);
    printf("C: (%.6f, %.6f)\n", t.c.x, t.c.y);
    printf("Area: %.6f\n", t.area);
}

int main(void) {
    double radius;
    double center_x;
    double center_y;
    
    printf("Enter the radius of the semicircle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Error: Invalid input for radius\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter the x-coordinate of the center: ");
    if (scanf("%lf", &center_x) != 1) {
        fprintf(stderr, "Error: Invalid input for center x-coordinate\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter the y-coordinate of the center: ");
    if (scanf("%lf", &center_y) != 1) {
        fprintf(stderr, "Error: Invalid input for center y-coordinate\n");
        return EXIT_FAILURE;
    }
    
    if (radius <= 0.0) {
        fprintf(stderr, "Error: Radius must be positive\n");
        return EXIT_FAILURE;
    }
    
    Triangle result = find_largest_triangle(radius, center_x, center_y);
    
    if (result.area < 1e-9) {
        fprintf(stderr, "Error: Could not find a valid triangle\n");
        return EXIT_FAILURE;
    }
    
    print_triangle(result);
    
    return EXIT_SUCCESS;
}