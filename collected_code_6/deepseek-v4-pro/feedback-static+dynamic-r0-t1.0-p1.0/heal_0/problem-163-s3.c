#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

double regular_polygon_area(int sides, double side_length) {
    if (sides < 3) {
        fprintf(stderr, "Error: A polygon must have at least 3 sides\n");
        return -1.0;
    }
    if (side_length <= 0) {
        fprintf(stderr, "Error: Side length must be greater than zero\n");
        return -1.0;
    }
    
    double area = (sides * side_length * side_length) / 
                  (4.0 * tan(M_PI / sides));
    return area;
}

int main(void) {
    int sides;
    double side_length;
    double area;
    
    printf("Enter number of sides: ");
    if (scanf("%d", &sides) != 1) {
        fprintf(stderr, "Error: Invalid input for sides\n");
        return EXIT_FAILURE;
    }
    
    printf("Enter side length: ");
    if (scanf("%lf", &side_length) != 1) {
        fprintf(stderr, "Error: Invalid input for side length\n");
        return EXIT_FAILURE;
    }
    
    area = regular_polygon_area(sides, side_length);
    
    if (area < 0) {
        return EXIT_FAILURE;
    }
    
    printf("Area of regular polygon: %.2f\n", area);
    
    return EXIT_SUCCESS;
}