#include <stdio.h>
#include <math.h>

double calculate_sector_area(double radius, double angle) {
    return (M_PI * pow(radius, 2) * (angle / 360.0));
}

int main() {
    double radius, angle;
    printf("Enter the radius of the circle: ");
    if (scanf("%lf", &radius) != 1) {
        fprintf(stderr, "Invalid input for radius\n");
        return 1;
    }
    printf("Enter the angle of the sector: ");
    if (scanf("%lf", &angle) != 1) {
        fprintf(stderr, "Invalid input for angle\n");
        return 1;
    }
    if (angle < 0 || angle > 360) {
        fprintf(stderr, "Angle must be between 0 and 360 degrees\n");
        return 1;
    }
    double area = calculate_sector_area(radius, angle);
    printf("The area of the sector is: %.2f\n", area);
    return 0;
}