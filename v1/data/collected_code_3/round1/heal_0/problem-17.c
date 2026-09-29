#include <stdio.h>

int squarePerimeter(int side) {
    return 4 * side;
}

int main() {
    int side;
    printf("Enter the side of the square: ");
    scanf("%d", &side);
    printf("The perimeter of the square is: %d", squarePerimeter(side));
    return 0;
}