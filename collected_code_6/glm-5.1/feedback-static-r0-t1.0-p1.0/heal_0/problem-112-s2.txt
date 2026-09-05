#include <stdio.h>

#define PI 3.14159265358979323846

double cylinder_perimeter(double radius, double height);

int main(void) {
    double radius = 4.0;
    double height = 9.0;

    double perimeter = cylinder_perimeter(radius, height);

    printf("%f\n", perimeter);

    return 0;
}

double cylinder_perimeter(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return 0.0;
    }

    return (2.0 * PI * radius) + (2.0 * height);
}