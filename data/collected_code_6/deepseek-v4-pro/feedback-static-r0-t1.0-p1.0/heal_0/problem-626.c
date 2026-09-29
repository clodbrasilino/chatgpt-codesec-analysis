#include <stdio.h>
#include <math.h>

double largest_inscribed_triangle_area(double radius) {
    if (radius <= 0) {
        return -1.0;
    }
    return radius * radius;
}

int main(void) {
    double radius;
    
    printf("Enter the radius of the semicircle: ");
    if (scanf("%lf", &radius) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    if (radius <= 0) {
        printf("Radius must be positive\n");
        return 1;
    }
    
    double area = largest_inscribed_triangle_area(radius);
    printf("Area of the largest inscribed triangle: %.2f\n", area);
    
    return 0;
}