#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double calculate_circumference(double radius) {
    if (radius < 0.0) {
        return -1.0;
    }
    return 2.0 * PI * radius;
}

int main(void) {
    double radius = 0.0;
    double circumference = 0.0;
    int scan_result = 0;

    printf("Enter the radius of the circle: ");
    scan_result = scanf("%lf", &radius);

    if (scan_result != 1) {
        fprintf(stderr, "Error: Invalid input. Please enter a numeric value.\n");
        return 1;
    }

    if (radius < 0.0) {
        fprintf(stderr, "Error: Radius cannot be negative.\n");
        return 1;
    }

    circumference = calculate_circumference(radius);

    if (circumference < 0.0) {
        fprintf(stderr, "Error: Failed to calculate circumference.\n");
        return 1;
    }

    printf("Circumference: %.6f\n", circumference);

    return 0;
}