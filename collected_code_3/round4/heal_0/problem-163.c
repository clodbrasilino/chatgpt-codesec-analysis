#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double calculatePolygonArea(int sides, double sideLength) {
    double area = (sides * pow(sideLength, 2)) / (4 * tan(PI / sides));
    return area;
}

int main() {
    int sides;
    double sideLength;

    printf("Enter the number of sides: ");
    scanf("%d", &sides);

    printf("Enter the length of a side: ");
    scanf("%lf", &sideLength);

    double area = calculatePolygonArea(sides, sideLength);

    printf("The area of the polygon is: %.2lf\n", area);

    return 0;
}