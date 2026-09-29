#include <stdio.h>

float findSurfaceArea(float radius) {
    float surfaceArea;
    surfaceArea = 4 * 3.14 * radius * radius;
    return surfaceArea;
}

int main() {
    float radius;
    printf("Enter the radius of the sphere: ");
    scanf("%f", &radius);
    float area = findSurfaceArea(radius);
    printf("The surface area of the sphere is %.2f\n", area);

    return 0;
}