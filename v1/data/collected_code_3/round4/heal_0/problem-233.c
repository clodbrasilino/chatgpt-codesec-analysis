#include <stdio.h>
#define PI 3.14159

double calculate_lateral_surface_area(double radius, double height) {
    return 2 * PI * radius * height;
}

int main() {
    double radius, height;
    printf("Enter radius of the cylinder: ");
    scanf("%lf", &radius);
    printf("Enter height of the cylinder: ");
    scanf("%lf", &height);
    double result = calculate_lateral_surface_area(radius, height);
    printf("The lateral surface area of the cylinder is: %.2lf\n", result);
    return 0;
}