#include <stdio.h>

int calculatePerimeter(int sideLength) {
    if(sideLength < 0) {
        printf("Invalid side length. It must be a positive integer.\n");
        return -1;
    }

    int perimeter = 4 * sideLength;
    return perimeter;
}

int main() {
    int sideLength;
    
    printf("Enter the side length of the square: ");
    scanf("%d", &sideLength);

    int perimeter = calculatePerimeter(sideLength);
    
    if(perimeter != -1) {
        printf("The perimeter of the square is: %d\n", perimeter);
    }

    return 0;
}