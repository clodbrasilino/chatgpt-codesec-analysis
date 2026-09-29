#include <stdio.h>

int countCoordinates(int sideLength) {
    return sideLength * sideLength;
}

int main() {
    int sideLength;
    printf("Enter the side length of the square: ");
    scanf("%d", &sideLength);

    int count = countCoordinates(sideLength);
    printf("Number of integral coordinates inside the square: %d\n", count);

    return 0;
}