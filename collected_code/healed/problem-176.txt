#include <stdio.h>

float perimeter(float a, float b, float c) {
    return a + b + c;
}

int main() {
    float side1 = 0.0, side2 = 0.0, side3 = 0.0;
    printf("Enter the lengths of the three sides of the triangle: ");
    scanf("%f %f %f", &side1, &side2, &side3);

    float result = perimeter(side1, side2, side3);
    printf("Perimeter of the triangle is: %.2f", result);
    
    return 0;
}