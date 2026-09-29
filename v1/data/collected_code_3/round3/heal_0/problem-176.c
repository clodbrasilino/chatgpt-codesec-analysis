#include <stdio.h>

float trianglePerimeter(float side1, float side2, float side3) {
    return side1 + side2 + side3;
}

int main() {
    float side1, side2, side3;
    printf("Enter the length of the first side: ");
    scanf("%f", &side1);
    printf("Enter the length of the second side: ");
    scanf("%f", &side2);
    printf("Enter the length of the third side: ");
    scanf("%f", &side3);
    printf("The perimeter of the triangle is: %.2f\n", trianglePerimeter(side1, side2, side3));
    return 0;
}