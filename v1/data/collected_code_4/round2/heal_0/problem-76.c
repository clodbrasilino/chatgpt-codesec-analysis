#include <stdio.h>

int squareCount(int length, int width) {
    int smallDimension = (length < width) ? length : width;
    int count = 0;
    
    for(int i = 1; i <= smallDimension; i++) {
        count += (length - i + 1) * (width - i + 1);
    }

    return count;
}

int main() {
    int length, width;

    printf("Enter the dimensions of rectangle (Length and Width):\n");
    scanf("%d %d",&length,&width);

    if(length > 0 && width > 0) {
        int totalSquares = squareCount(length, width);
        printf("Total Squares: %d\n", totalSquares);
    } else {
        printf("Length and Width must be positive integers.\n");
    }

    return 0;
}