#include <stdio.h>

double volumeOfCuboid(double length, double width, double height) {
    return length * width * height;
}

int main() {
    double length, width, height, volume;

    printf("Enter length of the cuboid: ");
    scanf("%lf", &length);

    printf("Enter width of the cuboid: ");
    scanf("%lf", &width);

    printf("Enter height of the cuboid: ");
    scanf("%lf", &height);

    volume = volumeOfCuboid(length, width, height);

    printf("Volume of the cuboid is %.2lf\n", volume);

    return 0;
}