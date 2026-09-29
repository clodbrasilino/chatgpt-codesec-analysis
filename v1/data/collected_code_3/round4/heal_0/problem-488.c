#include <stdio.h>
#include <math.h>

double findArea(double side) {
    double area = (5 * (side * side)) / (4 * tan(M_PI / 5));
    return area;
}

int main() {
    double side;
    printf("Enter the length of side of the Pentagon: ");
    scanf("%lf", &side);
    printf("Area of the Pentagon: %.2lf\n", findArea(side));
    return 0;
}