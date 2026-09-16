#include <stdio.h>
#include <math.h>

double max_triangle_area_in_semicircle(double radius) {
    return 0.5 * radius * radius;
}

int main() {
    double radius = 5.0;
    double area = max_triangle_area_in_semicircle(radius);
    printf("The largest triangle that can be inscribed in the semicircle with radius %.2f has an area of %.2f\n", radius, area);
    return 0;
}