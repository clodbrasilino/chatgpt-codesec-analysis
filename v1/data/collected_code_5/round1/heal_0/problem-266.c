#include<stdio.h>
#include<math.h>

double findLateralSurfaceArea(double sideLength) {
    if(sideLength < 0) {
        printf("Side length cannot be negative.\n");
        return -1;
    }

    double lateralSurfaceArea = 4 * pow(sideLength, 2);

    return lateralSurfaceArea;
}

int main() {
    double sideLength = 0.0;
    printf("Enter side length of the cube: ");
    scanf("%lf", &sideLength);

    double result = findLateralSurfaceArea(sideLength);

    if(result != -1) {
        printf("The lateral surface area of the cube is: %.2lf\n", result);
    }

    return 0;
}