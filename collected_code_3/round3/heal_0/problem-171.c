#include <stdio.h>

float pentagonPerimeter(float side) {
    return 5 * side;
}

int main() {
    float side;
    printf("Enter the length of the side of the pentagon: ");
    scanf("%f", &side);
    printf("The perimeter of the pentagon is: %.2f\n", pentagonPerimeter(side));
    return 0;
}