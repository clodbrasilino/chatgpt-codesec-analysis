#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double findLargestTriangle(double a, double b) {
    double area = (3 * sqrt(3) / 4) * (a * b);
    return area;
}

int main() {
    double a, b;
    printf("Enter the semi-major axis length: ");
    scanf("%lf", &a);
    printf("Enter the semi-minor axis length: ");
    scanf("%lf", &b);
    double area = findLargestTriangle(a, b);
    printf("The area of the largest inscribed triangle is: %.2lf\n", area);
    return 0;
}