#include <stdio.h>

double circle_diameter(double radius) {
    return 2 * radius;
}

int main(void) {
    double radius;
    double diameter;

    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    if (radius < 0) {
        fprintf(stderr, "Radius cannot be negative\n");
        return 1;
    }

    diameter = circle_diameter(radius);
    printf("Diameter: %.2f\n", diameter);

    return 0;
}