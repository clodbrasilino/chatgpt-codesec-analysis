#include <stdio.h>
#include <math.h>

double cylinder_perimeter(double radius, double height) {
    double circle_circumference = 2 * M_PI * radius;
    double rectangle_side = 2 * height;
    return circle_circumference + rectangle_side;
}

int main() {
    double radius = 5.0;
    double height = 10.0;
    double perimeter = cylinder_perimeter(radius, height);
    printf("%f\n", perimeter);
    return 0;
}