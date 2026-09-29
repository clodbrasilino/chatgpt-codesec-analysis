#include <stdio.h>

float pentagonPerimeter(float side) {
    if(side <= 0) {
        printf("Invalid side length entered.");
        return -1;
    }
    return 5.0 * side;
}

int main() {
    float side;
    printf("Enter the side length of the pentagon: ");
    scanf("%f", &side);
    float perimeter = pentagonPerimeter(side);
    if(perimeter != -1) {
        printf("The perimeter of the pentagon is: %.2f\n", perimeter);
    }
    return 0;
}