#include <stdio.h>

int countCoordinate(int sideLength) {
    if (sideLength <= 0) {
        printf("Input should be a positive integer value.\n");
        return -1;
    }
    return sideLength * sideLength;
}

int main() {
    int sideLength;
    printf("Enter the side length of square: ");
    scanf("%d", &sideLength);
    int noOfCoordinates = countCoordinate(sideLength);
    if(noOfCoordinates > -1) {
        printf("Number of integral coordinates inside the square: %d\n", noOfCoordinates);
    }
    return 0;
}