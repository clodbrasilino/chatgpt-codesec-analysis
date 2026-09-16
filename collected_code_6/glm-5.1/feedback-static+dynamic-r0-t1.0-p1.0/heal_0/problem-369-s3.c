#include <stdio.h>

double find_lateral_surface_area(double length, double width, double height) {
    return 2.0 * height * (length + width);
}

int main() {
    double l, w, h;
    if (scanf("%lf %lf %lf", &l, &w, &h) == 3) {
        if (l >= 0.0 && w >= 0.0 && h >= 0.0) {
            double area = find_lateral_surface_area(l, w, h);
            printf("%lf\n", area);
        }
    }
    return 0;
}