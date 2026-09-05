#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
    double x;
    double y;
} Point;

double calculate_distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double calculate_perimeter(Point a, Point b, Point c) {
    double side1 = calculate_distance(a, b);
    double side2 = calculate_distance(b, c);
    double side3 = calculate_distance(c, a);
    
    if (side1 <= 0 || side2 <= 0 || side3 <= 0) {
        return -1.0;
    }
    
    if (side1 + side2 <= side3 || side2 + side3 <= side1 || side1 + side3 <= side2) {
        return -1.0;
    }
    
    return side1 + side2 + side3;
}

int main(void) {
    Point p1, p2, p3;
    double perimeter;
    
    printf("Enter coordinates for point 1 (x y): ");
    if (scanf("%lf %lf", &p1.x, &p1.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter coordinates for point 2 (x y): ");
    if (scanf("%lf %lf", &p2.x, &p2.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter coordinates for point 3 (x y): ");
    if (scanf("%lf %lf", &p3.x, &p3.y) != 2) {
        fprintf(stderr, "Invalid input\n");
        return EXIT_FAILURE;
    }
    
    perimeter = calculate_perimeter(p1, p2, p3);
    
    if (perimeter < 0) {
        fprintf(stderr, "Invalid triangle: points are collinear or coincident\n");
        return EXIT_FAILURE;
    }
    
    printf("Perimeter: %.2f\n", perimeter);
    
    return EXIT_SUCCESS;
}