#include <stdio.h>
#include <math.h>

double calculate_cone_surface_area(double radius, double height) {
    double slant_height = sqrt(radius * radius + height * height);
    return M_PI * radius * (radius + slant_height);
}

int main() {
    double radius, height;
    printf("Enter the radius and height of the cone: ");
    if (scanf("%lf %lf", &radius, &height) != 2) {
        printf("Invalid input\n");
        return 1;
    }
    double surface_area = calculate_cone_surface_area(radius, height);
    printf("The surface area of the cone is: %.2f\n", surface_area);
    return 0;
}