#include <stdio.h>

double calculate_surface_area(double length, double width, double height) {
    if (length <= 0 || width <= 0 || height <= 0)
        return -1.0;

    double surfaceArea = 2 * (length * width + width * height + height * length);
    return surfaceArea;
}

int main() {
    double length, width, height;

    printf("Enter length of cuboid: ");
    scanf("%lf", &length);

    printf("Enter width of cuboid: ");
    scanf("%lf", &width);

    printf("Enter height of cuboid: ");
    scanf("%lf", &height);

    double surfaceArea = calculate_surface_area(length, width, height);

    if (surfaceArea == -1.0) {
        printf("Error: Values for length, width, and height should be positive.");
        return -1;
    }

    printf("The surface area of the cuboid is %lf.", surfaceArea);

    return 0;
}