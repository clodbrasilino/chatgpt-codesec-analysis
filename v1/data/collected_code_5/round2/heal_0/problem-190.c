#include <stdio.h>

int countCoordinates(int sideLength) {
    if (sideLength < 1) {
        printf("Invalid input. Side length should be greater than 0.\n");
        return -1;
    }

    return sideLength * sideLength;
}

int main() {
    int sideLength;

    printf("Enter the side length of square: ");
    if(scanf("%d", &sideLength) != 1) {
        printf("Error in input.\n");
        return -1;
    }

    int numberOfCoordinates = countCoordinates(sideLength);

    if (numberOfCoordinates != -1) {
        printf("Number of integral coordinates: %d\n", numberOfCoordinates);
    }

    return 0;
}