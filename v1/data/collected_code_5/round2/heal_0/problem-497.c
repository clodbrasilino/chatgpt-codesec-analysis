#include <math.h>
#include <stdio.h>

double surface_area_cone(double radius, double height) {
    if (radius < 0 || height < 0) {
        return -1.0;
    }
    double slantHeight = sqrt(radius * radius + height * height);
    double surfaceArea = M_PI * radius * (radius + slantHeight);
    return surfaceArea;
}

int main() {
    double radius, height;
    printf("Enter the radius and height of the cone:\n");
    if (scanf("%lf %lf", &radius, &height) != 2) {
        printf("Invalid input. Please enter two numbers separated by a space.\n");
        return 1;
    }

    double surfaceArea = surface_area_cone(radius, height);
    if (surfaceArea < 0) {
        printf("Invalid parameters. Radius and height should be positive.\n");
        return 1;
    }

    printf("The surface area of the cone is: %lf\n", surfaceArea);
    return 0;
}