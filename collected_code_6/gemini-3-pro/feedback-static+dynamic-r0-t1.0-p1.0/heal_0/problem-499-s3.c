#include <stdio.h>

double calculateDiameter(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * radius;
}

int main(void) {
    double radius = 0.0;
    double diameter = 0.0;
    int result = 0;

    printf("Enter the radius of the circle: ");
    result = scanf("%lf", &radius);

    if (result != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    diameter = calculateDiameter(radius);

    if (diameter < 0.0) {
        printf("Radius cannot be negative.\n");
        return 1;
    }

    printf("The diameter of the circle is: %.2f\n", diameter);

    return 0;
}