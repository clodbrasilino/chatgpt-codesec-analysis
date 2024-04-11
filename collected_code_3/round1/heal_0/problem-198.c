#include <stdio.h>
#include <math.h>

double largestTriangle(double a, double b) {
    return (sqrt(3) / 4) * (2 * a * b);
}

int main() {
    double a, b;
    printf("Enter the semi-major axis length: ");
    scanf("%lf", &a);
    printf("Enter the semi-minor axis length: ");
    scanf("%lf", &b);
    printf("The area of the largest inscribed triangle is: %.2lf\n", largestTriangle(a, b));
    return 0;
}