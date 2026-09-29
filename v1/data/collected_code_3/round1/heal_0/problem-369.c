#include <stdio.h>

float lateralSurfaceArea(float length, float width, float height) {
    return 2 * (length * height + width * height);
}

int main() {
    float length, width, height;
    printf("Enter length of the cuboid: ");
    scanf("%f", &length);
    printf("Enter width of the cuboid: ");
    scanf("%f", &width);
    printf("Enter height of the cuboid: ");
    scanf("%f", &height);
    printf("Lateral Surface Area of the cuboid is: %.2f\n", lateralSurfaceArea(length, width, height));
    return 0;
}