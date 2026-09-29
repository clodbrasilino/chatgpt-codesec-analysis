#include <stdio.h>

int countSquares(int length, int width) {
    return length * width;
}

int main() {
    int length = 5;
    int width = 4;
    int result = countSquares(length, width);
    printf("The number of squares in a rectangle of length %d and width %d is: %d\n", length, width, result);
    return 0;
}