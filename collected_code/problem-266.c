#include <stdio.h>

float lateralSurfaceArea(float side) {
    return 4 * (side * side);
}

int main() {
    float side;
    
    printf("Enter the side length of the cube: ");
    scanf("%f", &side);
    
    float lateralArea = lateralSurfaceArea(side);
    
    printf("The lateral surface area of the cube is %.2f\n", lateralArea);
    
    return 0;
}