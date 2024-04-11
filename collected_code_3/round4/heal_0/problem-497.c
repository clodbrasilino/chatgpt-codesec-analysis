#include <stdio.h>
#include <math.h>

#define PI 3.141592653589793238

double coneSurfaceArea(double radius, double height) {
    double slantHeight = sqrt(radius * radius + height * height);
    return PI * radius * (radius + slantHeight);
}

int main() {
    double radius, height;

    printf("Enter radius of the cone: ");
    scanf("%lf", &radius);
    printf("Enter height of the cone: ");
    scanf("%lf", &height);

    double surfaceArea = coneSurfaceArea(radius, height);

    printf("Surface area of the cone is: %.2lf\n", surfaceArea);

    return 0;
}