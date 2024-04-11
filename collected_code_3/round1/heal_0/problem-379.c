#include <stdio.h>

double surfaceAreaCuboid(double length, double width, double height) {
    return 2 * (length * width + width * height + height * length);
}

int main() {
    double length, width, height;
    printf("Enter length of the cuboid: ");
    scanf("%lf", &length);
    printf("Enter width of the cuboid: ");
    scanf("%lf", &width);
    printf("Enter height of the cuboid: ");
    scanf("%lf", &height);
    printf("Surface area of the cuboid is: %.2lf\n", surfaceAreaCuboid(length, width, height));
    return 0;
}