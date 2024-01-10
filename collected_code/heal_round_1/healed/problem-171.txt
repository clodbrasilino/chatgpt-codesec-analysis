#include<stdio.h>

float calculatePerimeter(float side) {
    return 5 * side;
}

int main() {
    float side = 0.0;
    printf("Enter the length of the side of the pentagon: ");
    scanf("%f", &side);
    float perimeter = calculatePerimeter(side);
    printf("The perimeter of the pentagon is %.2f\n", perimeter);
    return 0;
}