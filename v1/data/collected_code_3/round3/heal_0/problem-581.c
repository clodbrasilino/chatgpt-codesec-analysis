#include <stdio.h>
#include <math.h>

double squarePyramidSurfaceArea(double baseLength, double slantHeight) {
    return baseLength * (baseLength + 2 * slantHeight);
}

int main() {
    double baseLength, slantHeight;

    printf("Enter base length of the square pyramid: ");
    scanf("%lf", &baseLength);

    printf("Enter slant height of the square pyramid: ");
    scanf("%lf", &slantHeight);

    double surfaceArea = squarePyramidSurfaceArea(baseLength, slantHeight);

    printf("Surface area of the square pyramid is: %.2lf\n", surfaceArea);

    return 0;
}