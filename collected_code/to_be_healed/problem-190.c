#include <stdio.h>

int countCoordinates(int sideLength) {
    int count = 0;
    for (int x = 0; x <= sideLength; x++) {
        for (int y = 0; y <= sideLength; y++) {
            count++;
        }
    }
    return count;
}

int main() {
    int sideLength;
    printf("Enter the side length of the square: ");
    /* Possible weaknesses found:
     *  Cannot determine that 'sideLength' is initialized [premium-bughuntingUninit]
     */
    scanf("%d", &sideLength);
    int numCoordinates = countCoordinates(sideLength);
    printf("Number of integral coordinates inside the square: %d\n", numCoordinates);
    return 0;
}