#include <stdio.h>

double calculate_surface_area(double length, double width, double height) {
    return 2 * (length * width + width * height + height * length);
}

int main() {
    double length = 5.0;
    double width = 3.0;
    double height = 4.0;
    double surface_area = calculate_surface_area(length, width, height);
    printf("The surface area of the cuboid is: %.2f\n", surface_area);
    return 0;
}