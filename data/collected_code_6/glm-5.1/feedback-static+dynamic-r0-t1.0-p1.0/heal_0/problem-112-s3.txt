#include <stdio.h>
#include <math.h>

double cylinder_perimeter(double radius, double height) {
    if (radius < 0.0 || height < 0.0) {
        return -1.0;
    }
    return 2.0 * M_PI * radius + 2.0 * height;
}

int main(void) {
    double radius = 5.0;
    double height = 10.0;
    double perimeter = cylinder_perimeter(radius, height);
    if (perimeter < 0.0) {
        return 1;
    }
    printf("%f\n", perimeter);
    return 0;
}