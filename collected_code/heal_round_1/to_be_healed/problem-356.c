#include <stdio.h>

float findThirdAngle(float angle1, float angle2) {
    float angle3 = 180 - angle1 - angle2;
    return angle3;
}

int main() {
    float angle1, angle2, angle3;
    
    printf("Enter the first angle of the triangle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'angle1' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &angle1);
    
    printf("Enter the second angle of the triangle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'angle2' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &angle2);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'angle2' is initialized [premium-bughuntingUninit]
     *  Cannot determine that 'angle1' is initialized [premium-bughuntingUninit]
     */
    angle3 = findThirdAngle(angle1, angle2);
    
    printf("The third angle of the triangle is: %.2f\n", angle3);
    
    return 0;
}