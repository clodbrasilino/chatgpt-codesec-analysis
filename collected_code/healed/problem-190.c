#include <stdio.h>

int countCoordinates(int sideLength) {
    int count = 0;
    int x, y;
    for (x = 0; x <= sideLength; x++) {
        for (y = 0; y <= sideLength; y++) {
            count++;
        }
    }
    return count;
}

int main() {
    int sideLength = 0;
    printf("Enter the side length of the square: ");
    scanf("%d", &sideLength);
    if(sideLength > 0) {
        int numCoordinates = countCoordinates(sideLength);
        printf("Number of integral coordinates inside the square: %d\n", numCoordinates);
    } else {
        printf("Input is not valid");
    }
    return 0;
}