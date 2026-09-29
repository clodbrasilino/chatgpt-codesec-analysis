#include <stdio.h>
#include <math.h>

double surfaceAreaOfSquarePyramid(double baseLength, double slantHeight) {
    return baseLength * (baseLength + 2 * slantHeight);
}

int main() {
    double baseLength, slantHeight;

    printf("Enter base length of the square pyramid: ");
    scanf("%lf", &baseLength);

    printf("Enter slant height of the square pyramid: ");
    scanf("%lf", &slantHeight);

    printf("Surface area of the square pyramid is: %.2lf\n", surfaceAreaOfSquarePyramid(baseLength, slantHeight));

    return 0;
}