#include <stdio.h>

int countCoordinates(int sideLength) {
    return sideLength * sideLength;
}

int main() {
    int sideLength;
    printf("Enter the side length of the square: ");
    scanf("%d", &sideLength);

    int result = countCoordinates(sideLength);
    printf("The number of integral coordinates inside the square is: %d\n", result);

    return 0;
}