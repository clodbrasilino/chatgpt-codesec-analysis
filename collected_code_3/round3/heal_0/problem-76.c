#include <stdio.h>

int countSquares(int length, int width) {
    return length * width;
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