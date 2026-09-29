#include<stdio.h>

float calculateDiameter(float radius) {
    float diameter = 2 * radius;
    return diameter;
}

int main() {
    float radius, diameter;
    
    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);
    
    diameter = calculateDiameter(radius);
    
    printf("The diameter of the circle is %.2f\n", diameter);
    
    return 0;
}