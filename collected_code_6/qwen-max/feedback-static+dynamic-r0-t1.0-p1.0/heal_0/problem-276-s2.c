#include <stdio.h>
#include <math.h>

double calculate_cylinder_volume(double radius, double height) {
    return M_PI * pow(radius, 2) * height;
}

int main() {
    double radius = 3.0;
    double height = 5.0;
    double volume = calculate_cylinder_volume(radius, height);
    printf("Volume of the cylinder: %f\n", volume);
    return 0;
}