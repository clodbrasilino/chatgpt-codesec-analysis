#include <stdio.h>
#include <math.h>

float findLateralSurfaceArea(float radius, float height) {
    float slantHeight = sqrt(radius * radius + height * height);
    float lateralSurfaceArea = 3.14159 * radius * slantHeight;
    return lateralSurfaceArea;
}

int main() {
    float radius = 0.0f, height = 0.0f;
    printf("Enter the radius of the cone: ");
    scanf("%f", &radius);
    printf("Enter the height of the cone: ");
    scanf("%f", &height);
    float lateralSurfaceArea = findLateralSurfaceArea(radius, height);
    printf("Lateral Surface Area of the cone: %.2f\n", lateralSurfaceArea);
    return 0;
}