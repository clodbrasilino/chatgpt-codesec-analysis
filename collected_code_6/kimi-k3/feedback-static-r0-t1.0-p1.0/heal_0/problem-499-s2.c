#include <stdio.h>
#include <math.h>

double calculate_diameter(double radius) {
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
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    diameter = calculate_diameter(radius);

    if (diameter < 0.0) {
        fprintf(stderr, "Radius cannot be negative.\n");
        return 1;
    }

    printf("The diameter of the circle is: %.2f\n", diameter);

    return 0;
}