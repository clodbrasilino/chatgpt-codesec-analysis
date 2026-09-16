#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double largest_triangle_area(double radius) {
    if (radius <= 0.0) {
        return 0.0;
    }
    return radius * radius;
}

int main(void) {
    double radius = 0.0;
    
    if (scanf("%lf", &radius) != 1) {
        return EXIT_FAILURE;
    }
    
    if (radius <= 0.0) {
        return EXIT_FAILURE;
    }
    
    double area = largest_triangle_area(radius);
    printf("%f\n", area);
    
    return EXIT_SUCCESS;
}