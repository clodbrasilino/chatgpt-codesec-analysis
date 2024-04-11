#include <stdio.h>

int countSquares(int length, int width) {
    int squareCount = 0;
    for(int i = 1; i <= length && i <= width; i++) {
        squareCount += (length - i + 1) * (width - i + 1);
    }
    return squareCount;
}

int main() {
    int length, width;
    printf("Enter length of rectangle: ");
    scanf("%d", &length);
    printf("Enter width of rectangle: ");
    scanf("%d", &width);
    printf("Number of squares in rectangle: %d\n", countSquares(length, width));
    return 0;
}