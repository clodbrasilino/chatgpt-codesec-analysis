#include <stdio.h>
#include <math.h>

double largestTriangle(double radius) {
    return (radius * radius * M_PI) / 2;
}

int main() {
    double radius;
    printf("Enter the radius of the semicircle: ");
    scanf("%lf", &radius);
    printf("The area of the largest triangle that can be inscribed in the semicircle is: %.2lf\n", largestTriangle(radius));
    return 0;
}