#include <stdio.h>

int countCoordinates(int side) {
    return side * side;
}

int main() {
    int side;
    printf("Enter the side of the square: ");
    scanf("%d", &side);
    int count = countCoordinates(side);
    printf("Number of integral coordinates that lie inside a square: %d\n", count);
    return 0;
}