#include <stdio.h>

int findPerimeter(int side) {
    return 4 * side;
}

int main() {
    int side;
    printf("Enter the side of the square: ");
    scanf("%d", &side);
    printf("The perimeter of the square is: %d", findPerimeter(side));
    return 0;
}