#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793238

double calculateSurfaceArea(double radius, double height) {
    double slantHeight = sqrt((radius * radius) + (height * height));
    double surfaceArea = PI * radius * (radius + slantHeight);
    return surfaceArea;
}

int main() {
    double radius, height;
    printf("Enter radius of the cone: ");
    scanf("%lf", &radius);
    printf("Enter height of the cone: ");
    scanf("%lf", &height);
    double surfaceArea = calculateSurfaceArea(radius, height);
    printf("Surface Area of the cone is: %.2lf\n", surfaceArea);
    return 0;
}