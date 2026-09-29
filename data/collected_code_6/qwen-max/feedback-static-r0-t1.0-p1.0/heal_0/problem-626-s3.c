#include <stdio.h>
#include <math.h>

double find_largest_triangle_inscribed_in_semicircle(double radius) {
    return 0.5 * radius * radius;
}

int main() {
    double radius = 5.0;
    double area = find_largest_triangle_inscribed_in_semicircle(radius);
    printf("The area of the largest triangle inscribed in a semicircle with radius %.2f is %.2f\n", radius, area);
    return 0;
}