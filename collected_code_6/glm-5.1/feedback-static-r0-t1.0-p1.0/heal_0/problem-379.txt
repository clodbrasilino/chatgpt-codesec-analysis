#include <stdio.h>

double find_surface_area(double length, double width, double height) {
    double side1 = length * width;
    double side2 = length * height;
    double side3 = width * height;
    return 2.0 * (side1 + side2 + side3);
}

int main() {
    double l, w, h;
    if (scanf("%lf %lf %lf", &l, &w, &h) != 3) {
        return 1;
    }
    if (l <= 0.0 || w <= 0.0 || h <= 0.0) {
        return 1;
    }
    double area = find_surface_area(l, w, h);
    printf("%f\n", area);
    return 0;
}