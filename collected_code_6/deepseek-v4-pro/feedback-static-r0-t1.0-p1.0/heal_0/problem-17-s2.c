#include <stdio.h>

float square_perimeter(float side) {
    if (side <= 0) {
        return -1;
    }
    return 4 * side;
}

int main(void) {
    float side;
    
    printf("Enter the side length of the square: ");
    if (scanf("%f", &side) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    float perimeter = square_perimeter(side);
    
    if (perimeter < 0) {
        printf("Invalid side length\n");
        return 1;
    }
    
    printf("Perimeter of the square: %.2f\n", perimeter);
    
    return 0;
}