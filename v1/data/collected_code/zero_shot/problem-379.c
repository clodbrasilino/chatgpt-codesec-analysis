#include <stdio.h>

float findSurfaceArea(float length, float width, float height) {
    float surfaceArea = 2 * (length* width + length * height + width * height);
    return surfaceArea;
}

int main() {
    float length, width, height;
    printf("Enter the length, width, and height of the cuboid: ");
    scanf("%f %f %f", &length, &width, &height);
    
    float area = findSurfaceArea(length, width, height);
    printf("The surface area of the cuboid is: %.2f", area);
    
    return 0;
}