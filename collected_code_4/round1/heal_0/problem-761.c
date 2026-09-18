#include <stdio.h>
#include <math.h>

#define PI 3.14159265

double calculate_arc_length(double radius, double angle) {
    if (radius < 0 || angle < 0) {
        return -1;
    }

    double arc_length = 2 * PI * radius * (angle / 360);
    return arc_length;
}

int main() {
    double radius;
    double angle;

    printf("Enter the radius: ");
    scanf("%lf", &radius);
    printf("Enter the angle: ");
    scanf("%lf", &angle);

    double arc_length = calculate_arc_length(radius, angle);

    if (arc_length == -1) {
        printf("Error: Invalid input. Radius and angle must be non-negative values.\n");
    } else {
        printf("The arc length is: %.2lf\n", arc_length);
    }

    return 0;
}