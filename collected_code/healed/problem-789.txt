#include <stdio.h>
#include <math.h>

double calculatePerimeter(double sides, double length) {
    return sides * length;
}

int main() {
    double sides = 0.0, length = 0.0, perimeter = 0.0;

    printf("Enter the number of sides of the regular polygon: ");
    scanf("%lf", &sides);

    printf("Enter the length of each side: ");
    scanf("%lf", &length);

    perimeter = calculatePerimeter(sides, length);

    printf("The perimeter of the regular polygon is: %.2f\n", perimeter);
    
    return 0;
}