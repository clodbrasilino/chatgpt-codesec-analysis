#include <stdio.h>
#include <math.h>

double calculate_volume(double radius, double height) {
    return M_PI * pow(radius, 2) * height;
}

int main() {
    double radius, height;
    printf("Enter the radius of the cylinder: ");
    if (scanf("%lf", &radius) != 1) return 1;
    printf("Enter the height of the cylinder: ");
    if (scanf("%lf", &height) != 1) return 1;
    double volume = calculate_volume(radius, height);
    printf("The volume of the cylinder is: %f\n", volume);
    return 0;
}