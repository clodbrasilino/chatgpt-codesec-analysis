#include <stdio.h>

float findThirdAngle(float angle1, float angle2) {
    return 180 - (angle1 + angle2);
}

int main() {
    float angle1, angle2, angle3;

    printf("Enter first angle: ");
    scanf("%f", &angle1);

    printf("Enter second angle: ");
    scanf("%f", &angle2);

    angle3 = findThirdAngle(angle1, angle2);

    printf("Third angle of the triangle is: %.2f\n", angle3);

    return 0;
}