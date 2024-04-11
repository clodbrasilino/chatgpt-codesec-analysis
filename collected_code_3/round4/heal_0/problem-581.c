#include <stdio.h>
#include <math.h>

double surfaceAreaSquarePyramid(double base, double slantHeight) {
    return (base * base) + (2 * base * slantHeight);
}

int main() {
    double base, slantHeight;

    printf("Enter base of the square pyramid: ");
    scanf("%lf", &base);

    printf("Enter slant height of the square pyramid: ");
    scanf("%lf", &slantHeight);

    printf("Surface area of the square pyramid is: %.2lf\n", surfaceAreaSquarePyramid(base, slantHeight));

    return 0;
}