#include <stdio.h>

float findThirdAngle(float angle1, float angle2) {
    return 180 - angle1 - angle2;
}

int main() {
    float angle1 = 0.0, angle2 = 0.0, angle3 = 0.0;

    printf("Enter the first angle of the triangle: ");
    scanf("%f", &angle1);
    
    printf("Enter the second angle of the triangle: ");
    scanf("%f", &angle2);
    
    angle3 = findThirdAngle(angle1, angle2);
    
    printf("The third angle of the triangle is: %.2f\n", angle3);
    
    return 0;
}