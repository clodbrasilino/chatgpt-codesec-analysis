#include <stdio.h>

double sector_area(double radius, double angle) {
    return 0.5 * radius * radius * angle;
}

int main(void) {
    double radius, angle, area;

    printf("Enter radius: ");
    if (scanf("%lf", &radius) != 1 || radius <= 0) {
        printf("Invalid radius\n");
        return 1;
    }

    printf("Enter angle in degrees: ");
    if (scanf("%lf", &angle) != 1 || angle <= 0 || angle > 360) {
        printf("Invalid angle\n");
        return 1;
    }

    angle = angle * 3.14159265358979323846 / 180.0;
    area = sector_area(radius, angle);
    printf("Sector area: %.12f\n", area);

    return 0;
}