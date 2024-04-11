#include <stdio.h>

double calculatePerimeter(int sides, double sideLength) {
    return sides * sideLength;
}

int main() {
    int sides;
    double sideLength;

    printf("Enter the number of sides: ");
    scanf("%d", &sides);

    printf("Enter the length of a side: ");
    scanf("%lf", &sideLength);

    double perimeter = calculatePerimeter(sides, sideLength);

    printf("The perimeter of the polygon is: %.2lf\n", perimeter);

    return 0;
}