#include<stdio.h>

double findSurfaceArea(double radius, double height) {
    double baseArea = 3.14159 * radius * radius;
    double lateralArea = 2 * 3.14159 * radius * height;
    double surfaceArea = 2 * baseArea + lateralArea;
    return surfaceArea;
}

int main() {
    double radius = 0.0, height = 0.0;
    printf("Enter the radius of the cylinder: ");
    scanf("%lf", &radius);
    printf("Enter the height of the cylinder: ");
    scanf("%lf", &height);
    double area = findSurfaceArea(radius, height);
    printf("Surface area of the cylinder: %.2lf\n", area);

    return 0;
}