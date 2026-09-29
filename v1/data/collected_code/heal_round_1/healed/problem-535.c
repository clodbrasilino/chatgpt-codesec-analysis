#include<stdio.h>

double cylinderSurfaceArea(double radius) {
    double surfaceArea = 3.14 * radius * radius;
    return surfaceArea;
}

int main() {
    double radius = 0.0, height = 0.0;

    printf("Enter the radius and height of the cylinder: ");
    scanf("%lf %lf", &radius, &height);
    
    double topArea = cylinderSurfaceArea(radius);
    double bottomArea = cylinderSurfaceArea(radius);
    
    printf("The surface area of the top or bottom of the cylinder is: %.2lf", topArea);
    
    return 0;
}