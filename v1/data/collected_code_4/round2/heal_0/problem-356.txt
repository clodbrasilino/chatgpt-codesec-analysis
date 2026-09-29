#include <stdio.h>

float find_third_angle(float angle1, float angle2) {
    float angle3 = 180 - (angle1 + angle2);
    return angle3;
}

int main() {
    float angle1, angle2, angle3;
    
    printf("Enter the first angle: ");
    scanf("%f", &angle1);
    
    printf("Enter the second angle: ");
    scanf("%f", &angle2);

    if(angle1<0 || angle2<0 || angle1 + angle2 >= 180) {
        printf("Invalid angles.\n");
        return -1;
    }

    angle3 = find_third_angle(angle1, angle2);
    
    printf("The third angle is: %.2f\n", angle3);
    
    return 0;
}