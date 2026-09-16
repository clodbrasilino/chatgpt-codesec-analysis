#include <stdio.h>
#include <math.h>

double calculate_cylinder_surface_area(double radius, int top_or_bottom) {
    double area = 0.0;
    if (top_or_bottom == 1 || top_or_bottom == 2) {
        area = M_PI * pow(radius, 2);
    }
    return area;
}

int main() {
    double radius = 5.0;
    int top_or_bottom = 1; // 1 for top, 2 for bottom
    double area = calculate_cylinder_surface_area(radius, top_or_bottom);
    printf("The surface area is: %f\n", area);
    return 0;
}