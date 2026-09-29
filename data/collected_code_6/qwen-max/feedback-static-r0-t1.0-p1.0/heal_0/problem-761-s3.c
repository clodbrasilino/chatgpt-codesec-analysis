#include <stdio.h>
#include <math.h>

double calculate_arc_length(double radius, double angle_in_degrees) {
    double angle_in_radians = angle_in_degrees * (M_PI / 180.0);
    return radius * angle_in_radians;
}

int main() {
    double radius, angle_in_degrees;

    printf("Enter the radius: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius.\n");
        return 1;
    }

    printf("Enter the angle in degrees: ");
    if (scanf("%lf", &angle_in_degrees) != 1) {
        fprintf(stderr, "Invalid input for angle.\n");
        return 1;
    }

    if (radius < 0 || angle_in_degrees < 0) {
        fprintf(stderr, "Radius and angle must be non-negative.\n");
        return 1;
    }

    double arc_length = calculate_arc_length(radius, angle_in_degrees);
    printf("The arc length is: %lf\n", arc_length);

    return 0;
}