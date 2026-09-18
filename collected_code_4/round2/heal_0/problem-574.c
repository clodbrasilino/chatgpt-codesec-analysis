#include <stdio.h>
#include <math.h>

double getCylinderSurfaceArea(double radius, double height) {
    if (radius <= 0 || height <= 0) {
        return -1;
    }
    return 2 * M_PI * radius * (radius + height);
}

int main() {
    double radius, height;

    printf("Enter the radius of the cylinder: ");
    scanf("%lf", &radius);

    printf("Enter the height of the cylinder: ");
    scanf("%lf", &height);

    double surfaceArea = getCylinderSurfaceArea(radius, height);

    if(surfaceArea == -1) {
        printf("Radius and height should be greater than zero.\n");
    } else {
        printf("Surface area of the cylinder is %.2lf\n", surfaceArea);
    }

    return 0;
}