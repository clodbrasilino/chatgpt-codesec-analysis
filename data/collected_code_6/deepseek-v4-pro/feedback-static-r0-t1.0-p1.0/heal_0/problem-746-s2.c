#include <stdio.h>
#include <math.h>

#define PI 3.14159265358979323846

double sector_area(double radius, double angle_degrees) {
    if (radius < 0 || angle_degrees < 0) {
        return -1.0;
    }
    if (angle_degrees > 360.0) {
        angle_degrees = fmod(angle_degrees, 360.0);
    }
    double angle_radians = angle_degrees * PI / 180.0;
    return 0.5 * radius * radius * angle_radians;
}

int main(void) {
    double radius;
    double angle;
    int result;

    printf("Enter radius: ");
    result = scanf("%lf", &radius);
    if (result != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }

    printf("Enter angle in degrees: ");
    result = scanf("%lf", &angle);
    if (result != 1) {
        fprintf(stderr, "Invalid input for angle\n");
        return 1;
    }

    double area = sector_area(radius, angle);
    if (area < 0) {
        fprintf(stderr, "Radius and angle must be non-negative\n");
        return 1;
    }

    printf("Area of sector: %.4f\n", area);
    return 0;
}