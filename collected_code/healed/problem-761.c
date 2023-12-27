#include <stdio.h>

#define PI 3.14159

float calculateArcLength(float radius, float angle) {
    float arcLength;
    arcLength = (angle / 360) * (2 * PI * radius);
    return arcLength;
}

int main() {
    float radius = 0.0;
    float angle = 0.0;
    float result = 0.0;

    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);

    printf("Enter the angle in degrees: ");
    scanf("%f", &angle);

    result = calculateArcLength(radius, angle);

    printf("The arc length is: %f\n", result);

    return 0;
}