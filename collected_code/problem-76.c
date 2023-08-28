#include <stdio.h>

int countSquares(int width, int height) {
    int smallerSide = (width < height) ? width : height;
    int count = 0;

    for (int i = 1; i <= smallerSide; i++) {
        count += (width - i + 1) * (height - i + 1);
    }

    return count;
}

int main() {
    int width, height;
    
    printf("Enter the width and height of the rectangle: ");
    scanf("%d %d", &width, &height);
    
    int squares = countSquares(width, height);
    printf("Number of squares in the rectangle: %d\n", squares);
    
    return 0;
}