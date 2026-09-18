#include <stdio.h>

double sector_area(double radius, double angle_degrees) {
    if (radius < 0 || angle_degrees < 0) {
        return -1.0;
    }
    double full_circle_area = 22.0 / 7.0 * radius * radius;
    double angle_fraction = angle_degrees / 360.0;
    return full_circle_area * angle_fraction;
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

    printf("Area of sector: %.15g\n", area);
    return 0;
}