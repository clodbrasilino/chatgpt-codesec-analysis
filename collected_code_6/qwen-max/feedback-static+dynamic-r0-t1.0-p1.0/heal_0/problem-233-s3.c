#include <stdio.h>
#include <math.h>

double calculate_lateral_surface_area(double radius, double height) {
    return 2 * M_PI * radius * height;
}

int main() {
    double radius = 5.0;
    double height = 10.0;
    double lateral_surface_area = calculate_lateral_surface_area(radius, height);
    printf("Lateral Surface Area: %.2f\n", lateral_surface_area);
    return 0;
}