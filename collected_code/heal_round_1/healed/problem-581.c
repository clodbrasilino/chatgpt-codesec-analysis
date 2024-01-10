#include <stdio.h>
#include <math.h>

double surfaceAreaOfSquarePyramid(double sideLength, double height) {
    
    double baseArea = pow(sideLength, 2);
    double lateralArea = 2 * sideLength * sqrt(pow(sideLength / 2, 2) + pow(height, 2));
    double surfaceArea = baseArea + lateralArea;

    return surfaceArea;
}

int main() {
    double sideLength = 0.0;
    double height = 0.0;

    printf("Enter the side length of the square pyramid: ");
    scanf("%lf", &sideLength);

    printf("Enter the height of the square pyramid: ");
    scanf("%lf", &height);

    double area = surfaceAreaOfSquarePyramid(sideLength, height);

    printf("The surface area of the square pyramid is: %.2lf\n", area);

    return 0;
}