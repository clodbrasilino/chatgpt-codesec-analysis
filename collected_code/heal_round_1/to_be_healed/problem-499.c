#include<stdio.h>

float calculateDiameter(float radius) {
    float diameter = 2 * radius;
    return diameter;
}

int main() {
    float radius, diameter;
    
    printf("Enter the radius of the circle: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    scanf("%f", &radius);
    
    /* Possible weaknesses found:
     *  Cannot determine that 'radius' is initialized [premium-bughuntingUninit]
     */
    diameter = calculateDiameter(radius);
    
    printf("The diameter of the circle is %.2f\n", diameter);
    
    return 0;
}