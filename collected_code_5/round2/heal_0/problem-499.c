#include<stdio.h>
#include<math.h>

double getDiameter(double radius) {
    double diameter = 2*radius;
    return diameter;
}

int main() {
    double radius;
    printf("Enter the radius: ");
    if (scanf("%lf", &radius) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    if (radius < 0) {
        printf("Radius cannot be negative\n");
        return 1;
    }
    printf("Diameter of the circle: %.2f\n", getDiameter(radius));
    return 0;
}