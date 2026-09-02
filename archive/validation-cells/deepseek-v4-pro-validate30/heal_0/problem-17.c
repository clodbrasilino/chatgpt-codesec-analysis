#include <stdio.h>

int square_perimeter(int side) {
    if (side < 0) {
        return -1;
    }
    return 4 * side;
}

int main(void) {
    int side;
    int perimeter;
    
    printf("Enter side length: ");
    if (scanf("%d", &side) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    perimeter = square_perimeter(side);
    if (perimeter < 0) {
        printf("Invalid side length\n");
        return 1;
    }
    
    printf("Perimeter: %d\n", perimeter);
    return 0;
}