#include <stdio.h>

double surface_area(double length, double width, double height) {
    if (length <= 0.0 || width <= 0.0 || height <= 0.0) {
        return 0.0;
    }
    return 2.0 * (length * width + width * height + height * length);
}

int main() {
    double l = 2.0, w = 3.0, h = 4.0;
    double area = surface_area(l, w, h);
    printf("%f\n", area);
    return 0;
}