#include <stdio.h>

int countSquares(int length, int width) {
    int smallSide = length < width ? length : width;
    int count = 0;

    for (int i = 1; i <= smallSide; i++) {
        count += (length - i + 1) * (width - i + 1);
    }

    return count;
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